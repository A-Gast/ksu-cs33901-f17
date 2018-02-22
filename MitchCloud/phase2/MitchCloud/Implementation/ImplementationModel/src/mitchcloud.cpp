/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2 - Phase 2
 * Class implementations
 * mitchcloud.cpp
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"
#include <iostream>


/////////////////
// ProductDescription Class
ProductDescription::ProductDescription(int productID, std::string description, float price) {
	this->productID = productID;
	this->description = description;
	this->price = price;
}
int ProductDescription::getID() const { 
	return this->productID; 
}
std::string ProductDescription::getDescription() const { 
	return this->description; 
}
float ProductDescription::getPrice() const { 
	return this->price; 
}



/////////////////
// SalesLineItem Class
SalesLineItem::SalesLineItem(ProductDescription* desc, int qty) {
		this->description = desc;
		this->quantity = qty;
	}
float SalesLineItem::getSubTotal() const { 
	return quantity * description->getPrice(); 
}



/////////////////
// ProductCatalog Class
void ProductCatalog::addItem(int productID, ProductDescription* desc) { 
	this->descriptions[productID] = desc; 
}
ProductDescription* ProductCatalog::getDesc(int productID) { 
	ProductDescription* tmp = this->descriptions[productID]; 
	return tmp; 
}



/////////////////
// Payment Class
Payment::Payment(float cash) { 
	this->amount = cash; 
}
float Payment::getAmount() { 
	return this->amount; 
}


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
float Cart::getCartTotal() {
	float total;

	for(listItr it = cartItems.begin(); it != cartItems.end(); it++) {
		total += (*it)->getSubTotal();
	}
	return total;
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
void Order::makePayment(float cash) { 
	pmt = new Payment(cash); 
}
float Order::getOrderTotal() {
	float total;

	for(listItr it = orderItems.begin(); it != orderItems.end(); it++) {
		total += (*it)->getSubTotal();
	}
	return total;
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



/////////////////
// POS Class
void POS::checkOut() {
  this->order = new Order(cart->getCartList());

}
void POS::addCatalog() {
    catalog = new ProductCatalog();
    for(listItr it = descriptions.begin(); it != descriptions.end(); it++) {
        catalog->addItem((*it)->getID(), (*it));
    }
}
void POS::startNewOrder() {
	cart = new Cart();
}
//Print product description
void POS::findProduct(int id) {
  //ProductDescription* desc = catalog->getDesc(id);
  std::cout << catalog->getDesc(id)->getPrice() << std::endl;
}
void POS::createProducts() {
  ProductDescription* prod0 = new ProductDescription(100, "Vanilla", 3.50);
  ProductDescription* prod1 = new ProductDescription(105, "Chocolate", 3.50);
  ProductDescription* prod2 = new ProductDescription(110, "Strawberry", 3.75);
  ProductDescription* prod3 = new ProductDescription(117, "Coffee", 4.25);
  ProductDescription* prod4 = new ProductDescription(121, "Mint", 3.00);
  ProductDescription* prod5 = new ProductDescription(111, "French Vanilla", 4.00);
  ProductDescription* prod6 = new ProductDescription(129, "Moose Tracks", 4.25);
  ProductDescription* prod7 = new ProductDescription(115, "Fat-Free Vanilla", 5.00);
  ProductDescription* prod8 = new ProductDescription(160, "Lactose-Free Vanilla", 4.50);
  ProductDescription* prod9 = new ProductDescription(106, "Organic Vanilla", 5.50);
  descriptions.push_back(prod0);
  descriptions.push_back(prod1);
  descriptions.push_back(prod2);
  descriptions.push_back(prod3);
  descriptions.push_back(prod4);
  descriptions.push_back(prod5);
  descriptions.push_back(prod6);
  descriptions.push_back(prod7);
  descriptions.push_back(prod8);
  descriptions.push_back(prod9);
}
void POS::addToCart(int id, int qty) {
  ProductDescription* desc = catalog->getDesc(id);
    cart->makeLineItem(desc, qty);
}
void POS::removeFromCart(int id, int qty) {
    ProductDescription* desc = catalog->getDesc(id);
    cart->removeLineItem(desc, qty);
}
void POS::makePayment(float cash) {
	order->makePayment(cash);
	cart->becomeOrdered();	//Clears out cart (deletes products in it)
}
float POS::getCartTotal() {
  return cart->getCartTotal();
}
float POS::getChange() const {
	return order->getPay()->getAmount() - order->getOrderTotal();
}
