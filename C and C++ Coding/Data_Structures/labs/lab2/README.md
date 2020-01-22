Project Title: Colorfun

Motivation: This is a school project for CS302 Data Structures II.
The program takes an original .ppm image file and changes the colors
in the image. The color changes are based on different color maps like
black and white, rgb, cmyk, etc. Using interpolation the original
colors are converted to the new colors.

Build Status: There is a 'colorfun' executable as well as the .cpp and
.o files included in the folder. A makefile is also included that will
build the .cpp and .o files.

Code Style: Standard c++

Features: There are two processes that can be run in this program. The
first uses a threshold to convert old color to new color and the second
averages the values around each pixel to convert old color to new.

Installations: Need a working c/c++ environment such as gcc/g++ on linux.

Tests: There are .ppm image files and .txt files for testing purposes as
well as to demonstrate what this program does. Below shows how to use the
program.

How to Use: To run the colorfun program do 
	./colorfun -1|-2 -c 'name'.txt 'name'.ppm
where '-1|-2' is process 1 or process 2.

Credits: The assignment comes from the CS302 course at the University of
Tennessee

Program Author: Samuel C. Leonard
