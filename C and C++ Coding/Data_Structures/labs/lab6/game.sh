#! /bin/sh

R=$1
C=$2

mazemake ${R:=60} ${C:=80} > maze.txt
mazesolve < maze.txt > path.txt 

mazeshow 10 maze.txt | convert - maze.png
mazeshow 10 maze.txt path.txt | convert - maze_path.png
