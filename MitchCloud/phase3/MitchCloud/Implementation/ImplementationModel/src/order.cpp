/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2
 * Order Class
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"

/////////////////
// Order Class
Order::Order() {
	complete = false;
}
Order::Order(std::list<SalesLineItem*> cartItems) {
	//Copy items from cart to initialize order
	this->orderItems = cartItems;
	this->complete = false;
}
void Order::makePayment(double cash) { 
	pmt = new Payment(cash); 
}

bool Order::isComplete() const { 
	return complete; 
}
void Order::becomeComplete() { 	//Once order becomes complete, cart should terminate
	complete = true;
	//Delete payment
	delete pmt;
	//Delete list of sales line items
	for(listItr it = orderItems.begin(); it != orderItems.end(); it++) {
		delete *it;
	}
}
Payment* Order::getPay() const { 
	return pmt; 
}