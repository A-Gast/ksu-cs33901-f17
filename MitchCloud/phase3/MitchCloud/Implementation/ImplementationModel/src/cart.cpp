/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2
 * Cart Class
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"

/////////////////
// Cart Class
void Cart::makeLineItem(ProductDescription* desc, int qty) {
	SalesLineItem* tmp = new SalesLineItem(desc, qty);
	this->cartItems.push_back(tmp);
}
void Cart::removeLineItem(ProductDescription* desc, int qty) {
	SalesLineItem* tmp = new SalesLineItem(desc, qty);
	this->cartItems.remove(tmp);
}
double Cart::getCartTotal() {
	double total;
	for(listItr it = cartItems.begin(); it != cartItems.end(); it++) {
		total += (*it)->getSubTotal();
	}
	return total * this->discount;
}
bool Cart::isOrdered() { 
	return ordered; 
}
void Cart::becomeOrdered() {
	ordered = true;
	//Delete list of sales line items
	for(listItr it = cartItems.begin(); it != cartItems.end(); it++) {
		delete *it;
	}
}
std::list<SalesLineItem*> Cart::getCartList() {
	std::list<SalesLineItem*> tmp = this->cartItems;
	return tmp;
}
void Cart::setDiscount(double percentage) {
	//receieves a percentage discount
	//converts to necessary decimal
	percentage /= 100;
	percentage = 1 - percentage;
	this->discount = percentage;
}