/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2
 * Sales Line Item Class
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"

/////////////////
// SalesLineItem Class
SalesLineItem::SalesLineItem(ProductDescription* desc, int qty) {
	this->description = desc;
	this->quantity = qty;
	this->special = false;
	this->price = desc->getDiscount() * 5.50;
}
double SalesLineItem::getSubTotal() const {
	//assuming base price for weight is $5.50
	//and each unit 'quantity' is one set of weight 
	return quantity * price; 
}
std::string SalesLineItem::getName() {
	return (description->getDescription() + " " + description->getType());
}
int SalesLineItem::getQty() {
	return this->quantity;
}
void SalesLineItem::setSpecial(double specialPrice) {
	this->special = true;
	this->price = specialPrice;
}
bool SalesLineItem::isSpecial() {
	return this->special;
}
//overloaded for removing item from shopping cart.
//remove item still isnt working though
bool SalesLineItem::operator==(const SalesLineItem& rhs) const{
	// int quantity;
	// ProductDescription* description;
	if(this->description->getID() == rhs.description->getID()){
		return true;
	}
  return false;
}