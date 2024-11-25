Scanner Assignment 2:

UNI: srg2178

Demo Link: [https://youtu.be/nPv-uvyog6c](https://www.youtube.com/watch?v=SrL9LtiS1XM)


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
Output file: input1.java
****************************

Program:
        roomDec:
                roomID: cell
                STORY: "Welcome to the Pirate Ship Maze Game! Traverse the rooms collecting items along the way and try to find your way out. You are in the brig. Your cell door has been left unlocked. You can open the door and enter the hallway."
                roomItems: 
                exits: hallway 

        roomDec:
                roomID: hallway
                STORY: "You have entered the hallway. To your left is a staircase going up. On your right is a black door. Which one do you head towards?"
                roomItems: 
                exits: staircase blackDoor cell 

        roomDec:
                roomID: staircase
                STORY: "You head up the staircase and find yourself on the second level surrounded by sleeping pirates. You snatch a knife off a sleeping pirate. You can continue up the thirdFloor or head towards a green door at the end fo the room."
                roomItems: Knife 
                exits: greenDoor thirdFloor staircase 

        roomDec:
                roomID: blackDoor
                STORY: "You go through the black door and find barrels of whiskey and biscuits. There is not much else in here. You should probably head back."
                roomItems: Whiskey biscuits 
                exits: hallway 

        roomDec:
                roomID: greenDoor
                STORY: "You go through the green door and find yourself in the laundry. You can pick up some sheets. There are no other exits here, you should head back."
                roomItems: sheets 
                exits: staircase 

        roomDec:
                roomID: thirdFloor
                STORY: "You go up to the thirdFloor of the ship. You see a yellow door, a blue door, and a white door. Choose."
                roomItems: Whiskey biscuits 
                exits: yellow blue white staircase 

        roomDec:
                roomID: yellow
                STORY: "You enter a private cabin. Not much here but books."
                roomItems: books 
                exits: thirdFloor 

        roomDec:
                roomID: blue
                STORY: "You enter a private cabin. Nothing here, but out the window you can see a small tugboat attached to the ship."
                roomItems: 
                exits: thirdFloor 

        roomDec:
                roomID: white
                STORY: "You have entered the top deck of the ship. It looks like a tugboat is on your right tied to the ship. It looks like you might need some sheets to form a sail too and food for your journey. On your left are a bunch of closed chests. Head to the chests or the tugboat?"
                roomItems: 
                exits: chests tugboat thirdFloor 

        roomDec:
                roomID: chests
                STORY: "You open the chests and they're filled with fresh water. You should take one."
                roomItems: freshWater 
                exits: tugboat white 

        roomDec:
                roomID: tugboat
                STORY: "In order to escape in the tugboat you need supplies for your journey, a sheet for a sail, and a knife to cut the boat free."
                roomItems: freshWater Whiskey biscuits sheets Knife 
                exits: 

        Starting Items: itemD 
Successfully generated: input1.java
Successfully compiled: input1.java
----------------------------
****************************
Processing input file: input2.txt
Output file: input2.java
****************************
Failed to create a Room Declaration. Incomplete/Missing variables
A Room must have story, items, exits and there must be a 'startingItems' array
failed at parse_RoomDeclarations 
failed at point program_parse
Parsing failed. Follow preceding fail statements to track it down.
Parsing failed for input2.txt. Skipping Java file generation.
****************************
Processing input file: input3.txt
Output file: input3.java
****************************

Program:
        roomDec:
                roomID: roomA
                STORY: "you are in room A. You can enter room B"
                roomItems: itemA itemB 
                exits: roomB 

        roomDec:
                roomID: roomB
                STORY: "you are in room B. You can enter roomC or go back to roomA"
                roomItems: itemC itemD 
                exits: roomC roomA 

        roomDec:
                roomID: roomC
                STORY: "you completed the maze"
                roomItems: itemC itemD 
                exits: 

        Starting Items: itemD itemG 
Successfully generated: input3.java
Successfully compiled: input3.java
----------------------------
****************************
Processing input file: input4.txt
Output file: input4.java
****************************
Failed to create a Room Declaration. Incomplete/Missing variables
A Room must have story, items, exits and there must be a 'startingItems' array
failed at parse_RoomDeclarations 
failed at parse_RoomDeclarations 
failed at point program_parse
Parsing failed. Follow preceding fail statements to track it down.
Parsing failed for input4.txt. Skipping Java file generation.
****************************
Processing input file: input5.txt
Output file: input5.java
****************************

Program:
        roomDec:
                roomID: cell
                STORY: "Welcome to the Dungeon Maze Game! Find your way through the rooms collecting keys needed in order to escape. You have just woken up in a cell. You can exit the cell into the hallway"
                roomItems: 
                exits: hallway 

        roomDec:
                roomID: hallway
                STORY: "You walk down the hallway and come across a gold key. There is a red door and a brown door at the end of the hallway. Which door do you choose?"
                roomItems: goldKey 
                exits: redDoor brownDoor cell 

        roomDec:
                roomID: redDoor
                STORY: "You walk through the red door and find yourself in a closet that has a silverKey and a rope. You can go back into the hallway."
                roomItems: silverKey rope 
                exits: hallway 

        roomDec:
                roomID: brownDoor
                STORY: "You walk through the brown door and see a locked window to the outside. You need two keys to unlock the window and a rope to climb down to freedom."
                roomItems: silverKey rope goldKey 
                exits: 

        roomDec:
                roomID: unreferencedRoom
                STORY: "dead code so this will not generate"
                roomItems: this will not generate 
                exits: 

        Starting Items: itemD itemG 
Successfully generated: input5.java
Successfully compiled: input5.java
----------------------------
Installation Steps:
Install gcc and bash: apt-get update && apt-get install -y gcc bash
In the directory containing the downloaded files for this assignment,
Change permissions: chmod +x shell.sh
Run shell script using ./shell.sh
