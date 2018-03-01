#============================================================================
# Make file for TicTacToe
#
# Software Development - Kent State University
#
# Andrew Gast
#


###############################################################
# Variables
CPP      = g++

###############################################################
# The first rule is run if only make is typed
msg:
        @echo 'Targets are:'
        @echo '  tictactoe:'
        @echo '  clean:'

###############################################################
tictactoe : main.o tictactoe.o
        $(CPP) -o tictactoe main.o

main.o : main.cpp tictactoe.hpp
        $(CPP) -c main.cpp

tictactoe.o   : tictactoe.hpp tictactoe-v1.0.cpp
        $(CPP) -c tictactoe-v1.0.cpp

###############################################################
#This will clean up everything via "make clean"
clean:
        rm -f tictactoe
        rm -f *.o
