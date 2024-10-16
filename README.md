Scanner Assignment:

UNI: srg2178

Lexical Alphabet: [a-zA-Z0-9".{}]

Keywords:
- ROOM [a-zA-Z]+
- - String literal ["][a-zA-Z0-9]*["]
- while 
- exits
- story
- END
- updateExits
- input


Operators:
- notHas
- .
- "
- {
- }

Sample Input Programs Expected Output: (sample errors are in in input4.txt and input5.txt)

************
input1.txt
------------------
<ROOM, room>
<IDENTIFIER, roomA>
<LBRACE, {>
<STORY, story>
<STRING, "you are in room A. You can enter room B or room C">
<EXITS, exits>
<LBRACE, {>
<IDENTIFIER, roomB>
<IDENTIFIER, roomC>
<RBRACE, }>
<RBRACE, }>
<ROOM, room>
<IDENTIFIER, roomB>
<LBRACE, {>
<STORY, story>
<STRING, "you are in room B. This is a deadend.">
<EXITS, exits>
<LBRACE, {>
<IDENTIFIER, roomA>
<RBRACE, }>
<RBRACE, }>
<ROOM, room>
<IDENTIFIER, roomC>
<LBRACE, {>
<STORY, story>
<STRING, "you are in room C. You can enter room D.">
<EXITS, exits>
<LBRACE, {>
<IDENTIFIER, roomD>
<RBRACE, }>
<RBRACE, }>
<ROOM, room>
<IDENTIFIER, roomD>
<LBRACE, {>
<STORY, story>
<STRING, "you are in room D. You have completed the maze!">
<EXITS, exits>
<LBRACE, {>
<END, END>
<RBRACE, }>
<RBRACE, }>
<ROOM, room>
<IDENTIFIER, Player>
<LBRACE, {>
<ROOM, room>
<IDENTIFIER, currentRoom>
<RBRACE, }>
<WHILE, while>
<EXITS, exits>
<NOTHAS, notHas>
<STRING, "END">
<LBRACE, {>
<INPUT, input>
<LBRACE, {>
<IDENTIFIER, selection>
<RBRACE, }>
<UPDATEEXITS, updateExits>
<LBRACE, {>
<IDENTIFIER, Player>
<DOT, .>
<IDENTIFIER, currentRoom>
<STRING, "selection">
<RBRACE, }>
<RBRACE, }>
*************

************
input2.txt
---------------
<ROOM, room>
<IDENTIFIER, roomA>
<LBRACE, {>
<STORY, story>
<STRING, "you are in the only room">
<EXITS, exits>
<LBRACE, {>
<END, END>
<RBRACE, }>
<RBRACE, }>
<WHILE, while>
<EXITS, exits>
<NOTHAS, notHas>
<STRING, "END">
<LBRACE, {>
<INPUT, input>
<LBRACE, {>
<IDENTIFIER, selection>
<RBRACE, }>
<UPDATEEXITS, updateExits>
<LBRACE, {>
<IDENTIFIER, Player>
<DOT, .>
<IDENTIFIER, currentRoom>
<STRING, "selection">
<RBRACE, }>
<RBRACE, }>
<ROOM, room>
<IDENTIFIER, Player>
<LBRACE, {>
<ROOM, room>
<IDENTIFIER, currentRoom>
<RBRACE, }>
<WHILE, while>
<EXITS, exits>
<NOTHAS, notHas>
<STRING, "END">
<LBRACE, {>
<INPUT, input>
<LBRACE, {>
<IDENTIFIER, selection>
<RBRACE, }>
<UPDATEEXITS, updateExits>
<LBRACE, {>
<IDENTIFIER, Player>
<DOT, .>
<IDENTIFIER, currentRoom>
<STRING, "selection">
<RBRACE, }>
<RBRACE, }>
*************

************
input3.txt
-----------------
<ROOM, room>
<IDENTIFIER, roomA>
<LBRACE, {>
<STORY, story>
<STRING, "you are in room A. You can enter room B or room C">
<EXITS, exits>
<LBRACE, {>
<IDENTIFIER, roomB>
<RBRACE, }>
<RBRACE, }>
<ROOM, room>
<IDENTIFIER, roomB>
<LBRACE, {>
<STORY, story>
<STRING, "you are in room B. This is the end.">
<EXITS, exits>
<LBRACE, {>
<END, END>
<RBRACE, }>
<RBRACE, }>
*************

************
input4.txt
----------------
Error: Unterminated string literal
*************

************
input5.txt
-----------------
Unexpected character: &
*************

Installation Steps:
Install gcc and bash: apt-get update && apt-get install -y gcc bash
In the directory containing the downloaded files for this assignment,
Change permissions: chmod +x shell.sh
Run shell script using ./shell.sh
