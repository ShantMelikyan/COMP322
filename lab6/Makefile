# Name: Shant Melikyan
# Project: Wack a Mole!

# This is a Makefile for my lab assignment. It allows me to easily and accurately rebuild
# the lab assignment.


# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXEC_SPIRITD=spiritd
SRC_SPIRITD=spiritd.c
OBJ_SPIRITD=spiritd.o

EXEC_MOLE=mole
SRC_MOLE=mole.c
OBJ_MOLE=mole.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# that the correct command-line options are set
CC=gcc
CFLAGS=-g -Wall -Wextra

# Here is my default target for the Makefile.  When I type make, this first target will
# be created. I.e., all the executables
all: $(EXEC_MOLE) $(EXEC_SPIRITD)

# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# each time my source file is modified.

$(EXEC_SPIRITD): $(SRC_SPIRITD)
	$(CC) $(CFLAGS) -c $(SRC_SPIRITD)
	$(CC) $(CFLAGS) -o $@ $(OBJ_SPIRITD)

$(EXEC_MOLE): $(SRC_MOLE)
	$(CC) $(CFLAGS) -c $(SRC_MOLE)
	$(CC) $(CFLAGS) -o $@ $(OBJ_MOLE)


# By convention, I always have a target called
# "clean" that I used to define all temporary
# or intermediates.
clean:
	rm -f $(EXEC_SPIRITD) $(OBJ_SPIRITD) *~
	rm -f $(EXEC_MOLE) $(OBJ_MOLE) *~
