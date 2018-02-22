#============================================================================
# Make file for MitchCloud System
#
# Software Development - Kent State University
#
# Andrew Gast
#
###############################################################
# Compile mitchcloud
mitchcloud: main.o mitchcloud.o
	g++ -Wall -W -Wunused -std=c++11 -o mitchcloud main.o mitchcloud.o

main.o: main.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c main.cpp mitchcloud.cpp

mitchcloud.o: mitchcloud.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c mitchcloud.cpp

###############################################################
###############################################################
clean:
	rm -f *.o mitchcloud
