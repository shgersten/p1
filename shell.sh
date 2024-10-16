#!/bin/bash

# Compile the C program
gcc -o scanner scan.c

# Check if compilation was successful
if [ $? -ne 0 ]; then
  echo "Compilation failed. Please check your C program for errors."
  exit 1
fi

# Array of input files
input_files=("input1.txt" "input2.txt" "input3.txt" "input4.txt" "input5.txt")

# Loop through each input file and execute the program
for input_file in "${input_files[@]}"
do
  echo "****************************"
  echo "Processing input file: $input_file"
  echo "****************************"
  ./scanner "$input_file"
  echo "----------------------------"
done
