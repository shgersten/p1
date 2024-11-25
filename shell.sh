#!/bin/bash

#c compile
gcc -o scanner scanj.c

#check if compilation worked
if [ $? -ne 0 ]; then
  echo "Compilation broke"
  exit 1
fi

#input files
input_files=("input1.txt" "input2.txt" "input3.txt" "input4.txt" "input5.txt")

# Loop through each input file
for input_file in "${input_files[@]}"
do
  
  base_name=$(basename "$input_file" .txt)

  #create .java 
  output_file="${base_name}.java"

  echo "****************************"
  echo "Processing input file: $input_file"
  echo "Output file: $output_file"
  echo "****************************"

  #run the program
  program_output=$(./scanner "$input_file" "$output_file")

     #Show any fails that might have happened
    echo "$program_output"
  #Check if parsing failed
  if echo "$program_output" | grep -q "Parsing failed. Follow preceding fail statements to track it down."; then
    echo "Parsing failed for $input_file. Skipping Java file generation."
    continue
  fi

  #Check if the scanner generated
  if [ $? -eq 0 ]; then
    echo "Successfully generated: $output_file"

    #Compile java file
    javac "$output_file"

    #Check if it worked
    if [ $? -eq 0 ]; then
      echo "Successfully compiled: $output_file"
    else
      echo "Failed to compile: $output_file"
    fi
  else
    echo "Failed to process: $input_file"
  fi

  echo "----------------------------"
done
