/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2 - Phase 2
 * Testing main for mitchcloud.cpp
 * Author: Andrew Gast
 */

#include <iostream>
#include <fstream>
#include <string>

#include "mitchcloud.hpp"

int main(int argc, char *argv[]) {
  //Add a few item descriptions
  std::cout << "generating product catalog..." << std::endl;
  ProductCatalog* catalog = new ProductCatalog();
  /*
  catalog->addItem(prod0->getID(), prod0);
  catalog->addItem(prod1->getID(), prod1);
  catalog->addItem(prod2->getID(), prod2);
  catalog->addItem(prod3->getID(), prod3);
  catalog->addItem(prod4->getID(), prod4);
  */
  POS* pos = new POS();
  pos->addCatalog();
  std::cout << "User selects to start a new order." << std::endl;
  pos->startNewOrder();
  //std::cout << "Enter an item id to search..." << std::endl;
  //std::cout << "Search: 117. " << std::endl;
  //pos->findProduct(117);

  std::cout << "Add itemID 117 to cart..." << std::endl;
  pos->addToCart(117, 1);

  std::cout << "Start checkout please..." << std::endl;
  pos->checkOut();
  //std::cout << pos->order->getOrderTotal() << "   Is your total" << std::endl;
  std::cout << "Make payment with $10" << std::endl;
  pos->makePayment(10.00);
  //float rem = pos->getChange();
  //std::cout << "Change owed: $" << rem << std::endl;

  std::cout << "Sale completed." << std::endl;
  /* having access problems, didn't think about having to create multiple ways to access various classes when I create them within the POS class. This caused me issues and simply couldn't fix it in time.*/
  delete pos;







  return 0;

}
