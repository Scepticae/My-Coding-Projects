Project Title: Crypto

Motivation: This is a class assignment that uses steganography
to encode a message into an image and then decode the message 
from the image. It uses a specific seed number that is the key
to decoding the message.

Build Status: The folder has an executable called 'crypto' and
a makefile that can build the .cpp files

Code Style: Standard c++

Installations: The executable or make files require a c/c++
developer environment such as linux or visual studio.

Tests: There are two .ppm image files that can be used to test
the program by either inputting a method at the prompt or by
piping a file in from stdin on the command line.

How to Use: To encode a file which should be done first do,
	./crypto -seed=N -encode 'name'.ppm
where N is a number and then type message at prompt or,
	./crypto -seed=N -encode 'name'.ppm < message.txt
which will pipe the text files contents in to be encoded.
To decode the message do,
	./crypto -seed=N -decode 'name'_wmsg.ppm
where N is the same number encoded with.

Credits: This assignment was given by the University of Tennessee
for the Data Structures II course.

Program Author: Samuel C. Leonard
