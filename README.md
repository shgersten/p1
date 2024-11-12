Scanner Assignment 2:

UNI: srg2178

Lexical Alphabet: [a-zA-Z0-9"{}]

Grammar:

Program -> RoomDeclarations startingItems { Items }

RoomDeclarations -> epsilon | RoomDeclaration RoomDeclarations

RoomDeclaration -> ROOM id { story "STRING" items { Items } exits { ExitOptions } }

Items-> epsilon | id Items

ExitOptions -> epsilon | id ExitOptions

Terminals:
ROOM
id
{
}
story
STRING
exits
epsilon

Non Terminals:
1) Program
2) RoomDeclarations
3) RoomDeclaration
4) Items
5) ExitOptions

Expected Output:

****************************
Processing input file: input1.txt
****************************

Program:
        roomDec:
                roomID: roomA
                STORY: "you are in room A. You can enter room B"
                roomItems: itemA itemB 
                exits: roomB 

        roomDec:
                roomID: roomB
                STORY: "you are in room B. You can enter room E"
                roomItems: itemC itemD 
                exits: roomE 

        roomDec:
                roomID: roomE
                STORY: "you are in room E. You can enter room Z"
                roomItems: itemC itemD 
                exits: roomZ 

        Starting Items: itemD itemG 


----------------------------
****************************
Processing input file: input2.txt
****************************
Failed to create a Room Declaration. Incomplete/Missing variables
A Room must have story, items, exits and there must be a 'startingItems' array
failed at parse_RoomDeclarations 
failed at point program_parse
Parsing failed. Follow preceding fail statements to track it down.
----------------------------
****************************
Processing input file: input3.txt
****************************

Program:
        roomDec:
                roomID: roomA
                STORY: "you are in room A. You can enter room B"
                roomItems: itemA itemB 
                exits: roomB 

        roomDec:
                roomID: roomB
                STORY: "you are in room B. You have finished the maze"
                roomItems: itemC itemD 
                exits: 

        Starting Items: itemD itemG 


----------------------------
****************************
Processing input file: input4.txt
****************************
Failed to create a Room Declaration. Incomplete/Missing variables
A Room must have story, items, exits and there must be a 'startingItems' array
failed at parse_RoomDeclarations 
failed at parse_RoomDeclarations 
failed at point program_parse
Parsing failed. Follow preceding fail statements to track it down.
----------------------------
****************************
Processing input file: input5.txt
****************************

Program:
        roomDec:
                roomID: roomA
                STORY: "you are in room A. You can enter room B or room C"
                roomItems: itemA itemB 
                exits: roomB roomC 

        roomDec:
                roomID: roomB
                STORY: "you are in room B. You can go to room C."
                roomItems: itemA itemB 
                exits: roomC 

        roomDec:
                roomID: roomC
                STORY: "you are in room C. You can enter room D."
                roomItems: itemA itemB 
                exits: roomD 

        roomDec:
                roomID: roomD
                STORY: "you are in room D. You have completed the maze!"
                roomItems: itemA itemB 
                exits: 

        Starting Items: itemD itemG 


----------------------------

Installation Steps:
Install gcc and bash: apt-get update && apt-get install -y gcc bash
In the directory containing the downloaded files for this assignment,
Change permissions: chmod +x shell.sh
Run shell script using ./shell.sh
