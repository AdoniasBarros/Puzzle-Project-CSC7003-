# makefile -> to run any COMMAND use make COMMAND
# e.g make compile

#to show the help of the game
help:
	cat README.md
#to compile the game
compile:
	gcc main.c -o puzzle
#to execute the game
execute:
	puzzle
dictionary:
	more dic.txt
