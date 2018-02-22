/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2
 * Product Description Class
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"

/////////////////
// ProductDescription Class
ProductDescription::ProductDescription(int productID, std::string type, std::string description, std::string ingredients, bool organic, int stocked) {
	this->productID = productID;
	this->type = type;
	this->description = description;
	this->ingredients = ingredients;
	this->organic = organic;
	this->stocked = stocked;
	this->discount = 1;
}
int ProductDescription::getID() const { 
	return this->productID; 
}
std::string ProductDescription::getType() const { 
	return this->type; 
}
std::string ProductDescription::getDescription() const { 
	return this->description; 
}
std::string ProductDescription::getIngredients() const { 
	return this->ingredients; 
}
bool ProductDescription::isOrganic() const { 
	return this->organic; 
}
void ProductDescription::changeStock(ProductDescription* prod, int amount) {
  if((prod->stocked + amount) < 0) {
    std::cout << "Invalid supply. There are currently " << prod->stocked << " available." << std::endl;
  }else{ 
    prod->stocked += amount;
  }
}
int ProductDescription::getStock() const {
  return this->stocked;
}
void ProductDescription::setDiscount(double percentage) {
	//receieves a percentage discount
	//converts to necessary decimal
	percentage /= 100;
	percentage = 1 - percentage;
	this->discount = percentage;
}
double ProductDescription::getDiscount() {
	return this->discount;
}