![alt tag](https://github.com/cmerrill314/thiefs_dilemma/blob/master/thiefs_dilemma.jpg?raw=true)

# Thiefs Dilemma
A simple text-based C++ game that I made for a final project in my Intro to Computer Science II course (CS162) at Oregon State University.

# Plot Overview

In this game, you are a thief who takes refuge from a storm in what appears to be an abandoned castle. You plan on robbing the place
while you are there, but soon find out that there is a Princess trapped in the dungeon who needs you to find the "Dungeon Key" before the
cell floods. Now you have to navigate the castle and find hidden objects that eventually provide you with the necessary sword and shield
that you can use to slay a dragon in the tower who holds the dungeon key. The "dilemma" described is that you only have a max inventory
of 6 items, and it takes exactly six items to save the Princess. Meaning that all of the loot you find in the process must be discarded
if you want to do the right thing and rescue the princess.

# How It Works

The idea was to utilize polymorphism and OOP by creating generic Space objects. In this game, the space objects are the rooms of the 
castle. The Game class controls the actual logic of the game and main.cpp runs the program along with the main menu.

The .txt files included contain the ASCII art that is used in the game. 

