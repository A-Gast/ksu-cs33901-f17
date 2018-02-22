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
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <sstream>

/////////////////
// User Class - user logs into the system to use it
class User {
private:
  //customer = 0, clerk = 1, local manager = 2, cloud manager = 3, sales analyst = 4
  std::string accType;
  std::string username;
  std::string password;
public:
  //constructor
	User();
  User(std::string u, std::string p, std::string t);
  void changePriv(std::string);
  void changeUn(std::string);
  void changePw(std::string);
  std::string getName();
  std::string getPw();
  std::string getPriv();
};
/////////////////
// ProductDescription Class - holds info for all products based on productID
class ProductDescription {
private:
	int productID;
	std::string type;
	std::string description;
	std::string ingredients;
	bool organic;
  int stocked;
  double discount;
public:
	//Constructor
  ProductDescription(int productID, std::string type, std::string description, std::string ingredients, bool organic, int stocked);
	//Functions
	int getID() const;
	std::string getType() const;
	std::string getDescription() const;
	std::string getIngredients() const;
	bool isOrganic() const;
  void changeStock(ProductDescription* prod, int amount);
  int getStock() const;
  void setDiscount(double percentage);
  double getDiscount();
};

/////////////////
// SalesLineItem Class
class SalesLineItem {
private:
	int quantity;
	ProductDescription* description;
	bool special;
	double price;
public:
	//Constructor
	SalesLineItem(ProductDescription* desc, int qty);
	bool operator==(const SalesLineItem& rhs) const;
	//Functions
	std::string getName();
	double getSubTotal() const;
	int getQty();
	void setSpecial(double specialPrice);
	bool isSpecial();
};

/////////////////
// ProductCatalog Class - holds a map containing ProductDescription objects
class ProductCatalog {
private:
  typedef std::map<const int, ProductDescription*>::iterator mapItr;
  std::map<int, ProductDescription*> descriptions;

public:
  //Functions
  void addItem(int productID, ProductDescription* desc);
  ProductDescription* getDesc(int productID);
  void viewCatalog();
};

/////////////////
// Payment Class -- Only works with cash for now 11/11/2017
class Payment {
private:
	double amount;
public:
	//Constructor
	Payment(double cash);
	// Payment(int card);
	// Payment(std::string phone);
	//Functions
	double getAmount();
};

/////////////////
// Cart Class
class Cart {
private:
	typedef std::list<SalesLineItem*>::iterator listItr;	//iterator for list
	std::list<SalesLineItem*> cartItems;
	bool ordered;	//True if the cart has been sent to an order and finalized
	double discount;
public:
	Cart() {ordered = false; discount = 1;};
	void makeLineItem(ProductDescription* desc, int qty);
	void removeLineItem(ProductDescription* desc, int qty);
	double getCartTotal();
	bool isOrdered();
	void becomeOrdered();
	std::list<SalesLineItem*> getCartList();
	void setDiscount(double percentage);
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
	void makePayment(double cash);
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
	std::vector<std::string> authlist;
	typedef std::list<User*>::iterator ulistItr;
	std::list<User*> userlist;
	Cart* cart;
	Order* order;
	ProductCatalog* catalog;
	bool delivery;
  	int userAuthLevel = -1;
public:
	void buildAuthlist(std::ifstream& inFile);
	void buildUserlist(/*std::vector<std::string> authlist*/);
  	bool verify(std::string username, std::string password);
	void checkOut(bool web, bool sim);
	void createProducts(int productID, std::string type, std::string description, std::string ingredients, bool organic, int stocked);
	void createProducts(std::ifstream& inFile);
	void addCatalog();
	void startNewOrder();
	void findProduct(int id);
	void filterProducts(std::string query);
	void searchProducts(std::string query);
	void addToCart(int id, int qty);
	void removeFromCart(int id, int qty);
	void showCart();
	double getCartTotal();
	void makePayment(double cash);
	double getChange() const;
    void viewCat();
    void simTrans();
    void plugRule();
    int getPermission() {return this->userAuthLevel;};
    void addUser(std::string user, std::string pass, std::string accT);
    void editUser(std::string usr, int choice, std::string newinfo);
};

#endif
