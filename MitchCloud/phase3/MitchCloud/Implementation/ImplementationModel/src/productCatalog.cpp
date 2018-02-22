/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2
 * Product Catalog Class
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"

/////////////////
// ProductCatalog Class
void ProductCatalog::addItem(int productID, ProductDescription* desc) { 
	this->descriptions[productID] = desc; 
}
ProductDescription* ProductCatalog::getDesc(int productID) { 
	ProductDescription* tmp = this->descriptions[productID]; 
	return tmp; 
}
void ProductCatalog::viewCatalog() {
	std::cout << "ID\tType\t\tDesc" << std::endl;
	std::cout << "----------------------------------------------------------" << std::endl;
	for (mapItr it = descriptions.begin(); it != descriptions.end(); ++it) {
	  std::cout << it->first << "\t" << it->second->getType() << "\t\t" << it->second->getDescription() << '\n';
	//std::cout <<  id << "\t" << type << "\t\t" << desc << std::endl;
	}
}
