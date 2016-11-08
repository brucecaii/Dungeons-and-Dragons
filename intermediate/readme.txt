### COMP 345 Assignment 2 ###
Lance Lafontaine
26349188
November 7th 2016


### Compilation and Execution Instructions ###

This program must be run on a system with the following dependencies installed:
- CppUnit
- Doxygen
- SFML

After some initial investigation with running this program on the lab computers, I was not able to do it, due to the lack of administrator priviledges and required dependencies.

The program was compiled using dynamic libraries on a Linux system with the above dependencies and using the following command:

$ cd /path/to/submission/directory
$ g++ -g *.cpp /usr/lib/libcppunit.so -lsfml-graphics -lsfml-window -lsfml-system -o comp345build

To run the main program:

$ cd /path/to/submission/directory
$ ./comp345build

To run the CppUnit tests:

$ cd /path/to/submission/directory
$ ./comp345build test

To create the documentation:

$ cd /path/to/submission/directory
$ doxygen .


### Assignment Submission Contents ###

This assignment 2 submission implements the majority of the requirements stated, but not all of them.


The rule and requirements were gathered from:
- The d20 SRD rules (although no map or campaign-specific rules were found)
- The Assignment 1 specification
- The Assignment 2 specification
- The intermediate project delivery specification
- The final project delivery specification


The requirements that were not satisfied by this assigment are as follows:
- A user-interactive method for campaign management (linking maps together).
- The graphical portion of the map creation/editing (however the logic is complete and tested).
- The logic for verification of map validity is implemented, but it is not executed everytime a map is loaded or saved.

All other assignment requirements should be satisfied.

One important assumption was made for this assignment submission:
- The map boundary can be considered as if it had walls. Therefore, a character would not be able to traverse the map boundary yet still access an exit door.

More specific details are available in the Doxygen documentation pages.


