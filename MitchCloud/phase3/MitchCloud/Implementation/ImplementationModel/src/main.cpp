/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2 - Phase 3
 * Testing main for mitchcloud.cpp
 * Mock up POS testing client
 * Author: Andrew Gast
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "mitchcloud.hpp"
#include <chrono>
#include <thread>

void drawOrderMenu(POS*,bool,bool);

int main(int argc, char *argv[]) {
  bool web, simulate;
  bool quit = false;
  std::cout << "\nIn-store POS [0] or Web? [1]" << std::endl;
  std::cin >> web;
  std::cout << "Interactive [0] or Simulation? [1]" << std::endl;
  std::cin >> simulate;

  //Initiate file streams for reading in menu data and auth list.
  std::ifstream menu, auths;
  POS* pos = new POS();
  pos->createProducts(menu);
  pos->addCatalog();
  pos->buildAuthlist(auths);
  pos->buildUserlist();


  if(web) { //web selected
    if(simulate) { //simulation
      std::cout << "User logs in." << std::endl;
      pos->verify("METALLICA", "UNDERICE");
      std::cout << "User selects to start a new order." << std::endl;
      pos->startNewOrder();
      std::cout << "Enter an item id to search..." << std::endl;
      std::cout << "Search: 1. " << std::endl;
      pos->findProduct(1);
      std::cout << "Search: 10. " << std::endl;
      pos->findProduct(10);
      std::cout << "Search: 15. " << std::endl;
      pos->findProduct(15);

      std::cout << "Add 1 itemID 10 to cart..." << std::endl;
      pos->addToCart(10, 1);
      std::cout << "Add 2 itemID 15 to cart..." << std::endl;
      pos->addToCart(15, 2);

      std::cout << "User selects to show cart total." << std::endl;
      std::cout << std::fixed;
      std::cout << std::setprecision(2);
      std::cout << "Total: $" << pos->getCartTotal() << std::endl;
      std::cout << "Start checkout please..." << std::endl;
      std::cout << "User selects delivery option for $5" << std::endl;
      pos->checkOut(web, simulate); //false, true

      std::cout << "Make payment with $50" << std::endl;
      pos->makePayment(50.00);
      std::cout << std::fixed;
      std::cout << std::setprecision(2);
      std::cout << "Change owed: $" << pos->getChange() << std::endl;

      std::cout << "Sale completed." << std::endl;

    }else{ //interactive
      bool authorized = false;
      std::string user, pass;
      do {
        std::cout << "Login [1] or Create Account [2]" << std::endl;
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        if(choice == 1) {
          std::cout << "Enter Username: ";
          std::cin >> user;
          std::cout << "Enter Password: ";
          std::cin >> pass;
        }else{
          std::cout << "Enter Username: ";
          std::getline (std::cin, user);
          std::cout << "Enter Password: ";
          std::getline (std::cin, pass);
          pos->addUser(user, pass, "0");
          std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        //verifies credentials. returns true/false
        authorized = pos->verify(user, pass);
      } while(!authorized);
      std::cout << "Login successful." << std::endl;
//////////////////////////////////////////////////////////////////////////////
      //If user is a manager, offer special options.
      if(pos->getPermission() > 1 && pos->getPermission() < 4) {
        do{
          //////////////////////////////
          //manager options/////////////
          std::cout << "\nMENU-----\n1: Add Account\n2: Edit Account\n3: Add Promotion\n4: Cancel----------" << std::endl;
          int p;
          std::cin >> p;
          std::cin.ignore();
          switch(p) {
            case 1:
            {
              std::string nusr, npw, ntyp;
              std::cout << "Enter Username: ";
              std::getline (std::cin, nusr);
              std::cout << "Enter Password: ";
              std::getline (std::cin, npw);
              std::cout << "Account Type: !NUMBERS ONLY!\n[0:customer 1:Clerk 2:Manager 3:Cloud Manager 4:Sales analyst]" << std::endl;
              std::getline (std::cin, ntyp);
              pos->addUser(nusr, npw, ntyp);
            }
              break;
            case 2:
            {
              int p1;
              do{
                std::cout << "\nAccount\n----------\n1: Change Username\n2: Change Password\n3: Change Account Type\n4: Quit" << std::endl;
                std::cin >> p1;
                std::cin.ignore();
              }while(p1 > 3 || p1 < 1);
                std::string usr, newinfo;
                std::cout << "Enter Username for account to be changed\n";
                std::getline(std::cin, usr);
                std::cout << "Enter new info" << std::cout;
                //change info
                pos->editUser(usr, p1, newinfo);
              }
              break;
            case 3:
            {
              pos->plugRule();
            }
              break;
            case 4:
            {
              quit = true;
            }
              break;
          }     
        }while(!quit);

/////////////////////////////////////////////////////////////////////////
      }else if (pos->getPermission() == 4) {
        do{
          ///////////////////////////
         //sales analyst options
          std::cout << "\nMENU-----\n1: Generate Report\n2: Edit Account\n3: Cancel\n----------" << std::endl;

        }while(!quit);


//////////////////////////////////////////////////////////////////////////
      }else if (pos->getPermission() == 1) {
        do{
          /////////////////////////////
          //clerk options
          std::cout << "\nMENU-----\n1: Place Order\n2: Edit Account\n3: Cancel\n----------" << std::endl;
          int p;
          std::cin >> p;        
          switch(p) {
            case 1:
            {
              pos->startNewOrder();
              drawOrderMenu(pos, web, simulate);
            }
              break;
            case 2:
            {
              int p1;
              do{
                std::cout << "\nEmployee # 2231";
                std::cout << "\nAccount\n----------\n1: Change Username\n2: Change Password\n3: Quit" << std::endl;
                std::cin >> p1;
                std::cin.ignore();
              }while(p1 > 3 || p1 < 1);
                if(p1 == 2) {
                  break;
                }
                std::cout << "Enter your current username.\n";
                std::string newinfo, usr;
                std::getline(std::cin, usr);
                std::cout << "Enter the new info.\n";
                std::getline(std::cin, newinfo);
                //change info
                pos->editUser(usr, p1, newinfo);
              }
              break;
            case 3:
            {
              quit = true;
            }
              break;
          }
        }while(!quit);

///////////////////////////////////////////////////////////////////////////
      }else{
        do{
          //////////////////////////////
          //customer options
          std::cout << "\nMENU-----\n1: Place Order\n2: Edit Account\n3: Cancel\n----------" << std::endl;
          int picked;
          std::cin >> picked;
          switch(picked) {
            case 1:
            {
              pos->startNewOrder();
              drawOrderMenu(pos, web, simulate);
            }
              break;
            case 2:
            {
              int p1;
              do{
                std::cout << "\nAccount\n----------\n1: Change Username\n2: Change Password\n3: Quit" << std::endl;
                std::cin >> p1;
                std::cin.ignore();
              }while(p1 > 3 || p1 < 1);
                if(p1 == 3) {
                  break;
                }
                std::cout << "Enter your current username.\n";
                std::string newinfo, usr;
                std::getline(std::cin, usr);
                std::cout << "Enter the new info.\n";
                std::getline(std::cin, newinfo);
                //change info
                pos->editUser(usr, p1, newinfo);
              }
              break;
            case 3:
            quit = true;
              break;
          }
        }while(!quit);
      }
    }
  }else{ //in-store POS
    if(simulate) { //simulation
      std::cout << "User logs in." << std::endl;
      pos->verify("METALLICA", "UNDERICE");
      std::cout << "User selects to start a new order." << std::endl;
      pos->startNewOrder();
      std::cout << "Enter an item id to search..." << std::endl;
      std::cout << "Search: 1. " << std::endl;
      pos->findProduct(1);
      std::cout << "Search: 10. " << std::endl;
      pos->findProduct(10);
      std::cout << "Search: 15. " << std::endl;
      pos->findProduct(15);

      std::cout << "Add 1 itemID 10 to cart..." << std::endl;
      pos->addToCart(10, 1);
      std::cout << "Add 2 itemID 15 to cart..." << std::endl;
      pos->addToCart(15, 2);

      std::cout << "User selects to show cart total." << std::endl;
      std::cout << std::fixed;
      std::cout << std::setprecision(2);
      std::cout << "Total: $" << pos->getCartTotal() << std::endl;
      std::cout << "Start checkout please..." << std::endl;
      std::cout << "User selects delivery option for $5" << std::endl;
      pos->checkOut(web, simulate); //false, true

      std::cout << "Make payment with $50" << std::endl;
      pos->makePayment(50.00);
      std::cout << std::fixed;
      std::cout << std::setprecision(2);
      std::cout << "Change owed: $" << pos->getChange() << std::endl;

      std::cout << "Sale completed." << std::endl;
      

    }else{ //interactive
      bool authorized = false;
      std::string user, pass;
      do {
        std::cout << "Enter Username: ";
        std::cin >> user;
        std::cout << "Enter Password: ";
        std::cin >> pass;
        //verifies credentials. returns true/false
        authorized = pos->verify(user, pass);
      } while(!authorized);
      std::cout << "Login successful." << std::endl;
      pos->startNewOrder();
      drawOrderMenu(pos, web, simulate);
    }
  }
  delete pos;
  return 0;
}

////////////////////////////////////////////////
// Function to draw menu
void drawOrderMenu(POS* pos, bool web, bool simulate) {
  bool quit = false;
  do{
        std::cout << "\nMENU-----\n1: Search\n2: Filter\n3: Look up by ID\n";
        std::cout << "4: Add to cart\n5: Remove from cart\n6: Checkout\n7: View Cart\n8: Cancel\n----------" << std::endl;
        std::cout << "Products are sold by weight, all units are $5.50" << std::endl;
        int menuchoice;
        do{
          std::cin >> menuchoice;
          std::cin.ignore();
          } while(menuchoice < 1 || menuchoice > 9);
        std::string query;
        int prid, qty;
        switch(menuchoice) {
          case 1:
          {
            std::cout << "\nEnter search query: ";
            std::getline (std::cin, query);
            pos->searchProducts(query);
          }
            break;
          case 2:
          {
            std::cout << "\nApplicable Filters:\nIce Cream, Cake, Pie, Topping, flavor, etc.." << std::endl;
            std::getline (std::cin, query);
            pos->filterProducts(query);
          }
            break;
          case 3:
          {
            std::cout << "\nEnter product ID for ingredients/description [ID required]" << std::endl;
            std::cin >> prid;
            pos->findProduct(prid);
          }
            break;
          case 4:
          {
            std::cout << "\nAdd item to cart [ID & quantity required] " << std::endl;
            std::cout << "ID: ";
            std::cin >> prid;
            std::cout << "\nQuantity: ";
            std::cin >> qty;
            pos->addToCart(prid, qty);
          }
            break;
          case 5:
          {
            std::cout << "\nRemove item from cart [ID & quantity required]" << std::endl;
            std::cout << "ID: ";
            std::cin >> prid;
            std::cout << "\nQuantity: ";
            std::cin >> qty;
            pos->removeFromCart(prid, qty);
          }
            break;
          case 6:
          {
            std::cout << "\nCheckout selected." << std::endl;
            pos->checkOut(web,simulate); //false, false  -  simulate = simulation   web = web client
            std::cout << "\nHow will you be paying today? cash[1] or credit[2]" << std::endl;
            int ptype;
            do{
              std::cin >> ptype;
            } while(ptype < 1 || ptype > 2);
            if(ptype == 2) {
              pos->simTrans();
              pos->makePayment(pos->getCartTotal());
            }else{
              std::cout << "\nHow much cash are you paying with? [xx.xx]" << std::endl;
              double cash;
              std::cin >> cash;
              pos->makePayment(cash);
              std::cout << std::fixed;
              std::cout << std::setprecision(2);
              std::cout << "\nChange owed: $" << pos->getChange() << std::endl;
            }
            std::cout << "Sale completed." << std::endl;
            pos->startNewOrder();
            std::cout << "\n\nWould you like to continue[0] or log off[1]?" << std::endl;
            std::cin >> quit;
          }
            break;
          case 7:
          {
            pos->showCart();
          }
            break;
          case 8:
          {
            std::cout << "Are you sure you want to cancel your order?[y/n]" << std::endl;
            char ans;
            std::cin >> ans;
            if(ans == 'y' || ans == 'Y') {
              quit = true;
            }
          }
            break;
        }
      } while(!quit);
}