/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2 - Phase 2
 * Header for mitchcloud.cpp
 * Class definitions
 * mitchcloud.hpp
 * Author: Andrew Gast
 */

#ifndef MITCHCLOUD_HPP
#define MITCHCLOUD_HPP

#include <iostream>
#include <string>
#include <map>
#include <list>

/////////////////
// ProductDescription Class - holds info for all products based on productID
class ProductDescription {
private:
	int productID;
	std::string description;
	float price;
public:
	//Constructor
	ProductDescription(int productID, std::string description, float price);
	//~ProductDescription();
	//Functions
	int getID() const;
	std::string getDescription() const;
	float getPrice() const;
};

/////////////////
// SalesLineItem Class
class SalesLineItem {
private:
	int quantity;
	ProductDescription* description;
public:
	//Constructor
	SalesLineItem(ProductDescription* desc, int qty);
	//Functions
	float getSubTotal() const;
};

/////////////////
// ProductCatalog Class - holds a map containing ProductDescription objects
class ProductCatalog {
private:
	std::map<int, ProductDescription*> descriptions;
public:
	//Functions
	void addItem(int productID, ProductDescription* desc);
	ProductDescription* getDesc(int productID);
};

/////////////////
// Payment Class -- Only works with cash for now 11/11/2017
class Payment {
private:
	float amount;
public:
	//Constructor
	Payment(float cash);
	//Functions
	float getAmount();
};

/////////////////
// Cart Class
class Cart {
private:
	typedef std::list<SalesLineItem*>::iterator listItr;	//iterator for list
	std::list<SalesLineItem*> cartItems;
	bool ordered;	//True if the cart has been sent to an order and finalized
public:
	void makeLineItem(ProductDescription* desc, int qty);
	void removeLineItem(ProductDescription* desc, int qty);
	float getCartTotal();	//Total in cart, does not include tax or shipping
	bool isOrdered();
	void becomeOrdered();
	std::list<SalesLineItem*> getCartList();
};

/////////////////
// Order Class
class Order {
private:
	typedef std::list<SalesLineItem*>::iterator listItr;	//iterator for list
	std::list<SalesLineItem*> orderItems;
	bool complete;	//True if the order is placed and paid
	Payment* pmt;
public:
	//Constructor **Should be created from Cart **NOT FINISHED
	Order();
	Order(std::list<SalesLineItem*>);
	//Functions
	void makePayment(float cash);
	float getOrderTotal();		//Total for order, includes tax + shipping fees
	//double & getBalance() { return pmt->getAmount() - getTotal(); }
	bool isComplete() const;
	void becomeComplete();
	Payment* getPay() const;
};

/////////////////
// POS Class
class POS {
private:
	typedef std::list<ProductDescription*>::iterator listItr;
	std::list<ProductDescription*> descriptions;
	Cart* cart;
	Order* order;
	ProductCatalog* catalog;
public:
	void checkOut();
  void createProducts();
	void addCatalog();
	void startNewOrder();
	void findProduct(int id);
	void addToCart(int id, int qty);
	void removeFromCart(int id, int qty);
	float getCartTotal();
	void makePayment(float cash);
	float getChange() const;
};

#endif
