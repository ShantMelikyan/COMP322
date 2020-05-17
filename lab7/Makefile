# Name: Shant Melikyan
# Project: 

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.

# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 

EXECUTABLE1=matrix_gen
SRC=matrix_gen.c
OBJ=matrix_gen.o

EXECUTABLE2=matrix_add
SRC2=matrix_add.c
OBJ2=matrix_add.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXECUTABLE1) $(EXECUTABLE2)

# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.
$(EXECUTABLE1): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
$(EXECUTABLE2): $(SRC2)
	$(CC) $(CFLAGS) -c $(SRC2)
	$(CC) $(CFLAGS) -o $@ $(OBJ2)

# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXECUTABLE1) $(OBJ) *~
	rm -f $(EXECUTABLE2) $(OBJ2) *~
