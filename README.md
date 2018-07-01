# 3D-Tic-Tac-Toe

A fairly intelligent bot, against which you can play a 3D version of the popular tic-tac-toe game.

This bot was developed as a part of the course *COL333: Principles of Artificial Intelligence* in Fall Semester, 2017-18. 

## About the game:
We will be playing the game against the bot on a 3x3x3 cube, where the objective is to successfully capture as many number of collinear lines that can be obtained on the cube, by successfully selecting 3 sets of distinct coordinates (i, j, k).

## Game instructions:
Since the bot works using the principle of a [Magic Cube](https://en.wikipedia.org/wiki/Magic_cube) to play against you, it provides you the option of either giving it a Cube yourself, or asking the bot to generate a cube. The bot will then take a couple of moments to generate and print for you a Magic Cube, which can then be used to play the game.

After printing the game, you can decide whether you want to play first or not. At every turn, you choose the coordinates of the cube you want to occupy, by *entering the value of the Magic Number corresponding to those coordinates.* This makes giving your moves to the computer much easier. However with simple modifications to the source file this can be easily changed. 

After 20 moves, the game stops and bot announces who the winner is, or whether both you and the both were equally good. Don't worry, the bot will not cheat!

## Building the game:
Building the game and playing it is very easy. Please see the instructions below for building the game:

1. `chmod +x build.sh`
2. `./build.sh`
3. `./game`

And the game will run! 
