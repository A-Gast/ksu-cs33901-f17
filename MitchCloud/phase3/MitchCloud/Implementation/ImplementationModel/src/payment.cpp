/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2
 * Payment Class
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"

/////////////////
// Payment Class
Payment::Payment(double amt) { 
	this->amount = amt; 
}
// Payment::Payment(int card) { 
// 	this->amount = amt; 
// }
// Payment::Payment(std::string phone) { 
// 	this->amount = amt; 
// }
double Payment::getAmount() { 
	return this->amount; 
}