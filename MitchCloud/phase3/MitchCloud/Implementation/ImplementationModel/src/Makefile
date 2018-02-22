#============================================================================
# Make file for MitchCloud System
#
# Software Development - Kent State University
#
# Andrew Gast
#
###############################################################
###############################################################
# Compile mitchcloud
mitchcloud: main.o productDescription.o salesLineItem.o productCatalog.o payment.o cart.o order.o pos.o user.o
	g++ -Wall -W -Wunused -std=c++11 -o mitchcloud main.o productDescription.o salesLineItem.o productCatalog.o payment.o cart.o order.o pos.o user.o


main.o: main.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c main.cpp productDescription.cpp salesLineItem.cpp productCatalog.cpp payment.cpp cart.cpp order.cpp pos.cpp user.cpp

productDescription.o : productDescription.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c productDescription.cpp

salesLineItem.o : salesLineItem.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c salesLineItem.cpp

productCatalog.o : productCatalog.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c productCatalog.cpp

payment.o : payment.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c payment.cpp

cart.o : cart.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c cart.cpp

order.o : order.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c order.cpp

pos.o : pos.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c pos.cpp

user.o : user.cpp mitchcloud.hpp
	g++ -Wall -W -Wunused -std=c++11 -c user.cpp

###############################################################
clean:
	rm -f *.o mitchcloud
