/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2
 * POS Class
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"
#include <iomanip>
#include <algorithm> 
#include <chrono>
#include <thread>

/////////////////
// POS Class
void POS::addUser(std::string user, std::string pass, std::string accT) {
  std::transform(user.begin(), user.end(), user.begin(), std::ptr_fun<int, int>(std::toupper));
  std::transform(pass.begin(), pass.end(), pass.begin(), std::ptr_fun<int, int>(std::toupper));
  //std::transform(accT.begin(), accT.end(), accT.begin(), std::ptr_fun<int, int>(std::toupper));
  std::string tmp = user + "," + pass + "," + accT;
  this->authlist.push_back(tmp);
  std::ofstream out;
  out.open("../data/auths.txt", std::ios::app);
  out << tmp;
  out << "\n";
  out.close();
  User* tmp2 = new User(user, pass, accT);
  this->userlist.push_back(tmp2);
}
void POS::editUser(std::string usr, int choice, std::string newinfo) {
  std::transform(usr.begin(), usr.end(), usr.begin(), std::ptr_fun<int, int>(std::toupper));
  for(ulistItr it = userlist.begin(); it != userlist.end(); ++it){
    if(usr == (*it)->getName()) {
      switch(choice) {
      case 1:
        {
          (*it)->changeUn(newinfo);
          // addUser(usr, (*it)->getPw(), (*it)->getPriv());
        }
          break;
        case 2:
        {
          (*it)->changePw(newinfo);
          // addUser(usr, (*it)->getPw(), (*it)->getPriv());
        }
          break;
        case 3:
        {
          (*it)->changePriv(newinfo);
          // addUser(usr, (*it)->getPw(), (*it)->getPriv());
        }
          break;
      }
    }
  }
}
void POS::buildUserlist(/*std::vector<std::string> authlist*/) {
  std::string s_user, s_pass, s_clearance;
  for(auto it = this->authlist.cbegin(); it != this->authlist.cend(); ++it) {
    std::stringstream linestream(*it);
    getline(linestream, s_user,  ',' );
    getline(linestream, s_pass,  ',' );
    getline(linestream, s_clearance,  ',' );
    User* tmp = new User(s_user, s_pass, s_clearance);
    this->userlist.push_back(tmp);
  }
}
void POS::buildAuthlist(std::ifstream& inFile) {
  inFile.open("../data/auths.txt");
  if (!inFile) {
    std::cout << "Unable to open file";
    exit(1); // terminate with error
  }
  std::string line;
  while(getline(inFile, line)) {
    this->authlist.push_back(line);
  }
  inFile.close();
}

bool POS::verify(std::string username, std::string password) {
  std::string s_user, s_pass, s_clearance;

  for(auto it = authlist.cbegin(); it != authlist.cend(); ++it) {
    std::stringstream linestream(*it);
    getline(linestream, s_user,  ',' );
    getline(linestream, s_pass,  ',' );
    getline(linestream, s_clearance,  ',' );

    if((s_user == username) && (s_pass == password)) {
      userAuthLevel = stoi(s_clearance);
      return true;
    }
  }
  std::cout << "\nInvalid username or password" << std::endl;
  return false;
}

void POS::checkOut(bool web, bool sim) {
  this->order = new Order(cart->getCartList());
  if(!sim && web) { //if not simulating and on web, offer pickup or delivery.
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << "\n$" << getCartTotal() << " is your total." << std::endl;
    std::cout << "\nWould you like pickup[0] or delivery?[1]" << std::endl;
    std::cout << "Delivery will cost $5.00" << std::endl;
    bool choice = false;
    std::cin >> choice;
    if(choice == 1) {
      delivery = true;
    }else{
      delivery = false;
    }
  }else if(!sim && !web){ //if not simulation and is in-store POS
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << "\n$" << getCartTotal() << " is your total." << std::endl;    
  }else if(sim && web) { //if simulation and on web, auto pick delivery
    delivery = true;
  }else {
    delivery = false;
  }
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
//Print product description by ID
void POS::findProduct(int id) {
  ProductDescription* desc = catalog->getDesc(id);
  std::string org = "";
  if(desc->isOrganic()) {
    org = "Organic";
  }
  if(desc->getIngredients() != ""){
      std::cout << "ID: " << desc->getID() << "  Description: " << desc->getDescription() << " " << desc->getType() << "\nMore info: " << desc->getIngredients() << "   " << org << std::endl;
  }else{
    std::cout << "ID: " << desc->getID() << "  Description: " << desc->getDescription() << " " << desc->getType() << "   " << org << std::endl;
  }
}
void POS::filterProducts(std::string query) {
  std::transform(query.begin(), query.end(), query.begin(), std::ptr_fun<int, int>(std::toupper));
  std::cout << "Using filter: " << query << std::endl;
  for(listItr it = descriptions.begin(); it != descriptions.end(); it++) {
      std::string tmp1 = (*it)->getType();
      std::string tmp2 = (*it)->getDescription();
      //std::string tmp3 = (*it)->getIngredients();
      std::string tmp4;
      //Get whether or not it is organic
      bool tmpOrganic = (*it)->isOrganic();
      if(tmpOrganic) {
        tmp4 == "ORGANIC";
      }
      //transform all items being searched
      std::transform(tmp1.begin(), tmp1.end(), tmp1.begin(), std::ptr_fun<int, int>(std::toupper));
      std::transform(tmp2.begin(), tmp2.end(), tmp2.begin(), std::ptr_fun<int, int>(std::toupper));
      //std::transform(tmp3.begin(), tmp3.end(), tmp3.begin(), std::ptr_fun<int, int>(std::toupper));

      std::size_t foundType = tmp1.find(query);
      std::size_t foundDesc = tmp2.find(query);
      //std::size_t foundIngred = tmp3.find(query);
      std::size_t foundOrganic = tmp4.find(query);

      if((foundType != std::string::npos) || (foundDesc != std::string::npos) || (foundOrganic != std::string::npos)) {
        std::cout << "ID: " << (*it)->getID() << "  Description: " << (*it)->getDescription() << " " << (*it)->getType() << "\n";
        std::cout << "\t" << (*it)->getIngredients() << std::endl;
      }
  }
}
void POS::searchProducts(std::string query) {
  int found = 0;
  //transform to uppercase for the searching
  std::transform(query.begin(), query.end(), query.begin(), std::ptr_fun<int, int>(std::toupper));
  for(listItr it = descriptions.begin(); it != descriptions.end(); it++) {
    std::string tmp1 = (*it)->getType();
    std::string tmp2 = (*it)->getDescription();
    std::string tmp3 = (*it)->getIngredients();
    //transform all items being searched
    std::transform(tmp1.begin(), tmp1.end(), tmp1.begin(), std::ptr_fun<int, int>(std::toupper));
    std::transform(tmp2.begin(), tmp2.end(), tmp2.begin(), std::ptr_fun<int, int>(std::toupper));
    std::transform(tmp3.begin(), tmp3.end(), tmp3.begin(), std::ptr_fun<int, int>(std::toupper));

    std::size_t foundType = tmp1.find(query);
    std::size_t foundDesc = tmp2.find(query);
    std::size_t foundIngred = tmp3.find(query);

    if((foundType != std::string::npos) || (foundDesc != std::string::npos) || (foundIngred != std::string::npos)) {
      std::cout << "ID: " << (*it)->getID() << "  Description: " << (*it)->getDescription() << " " << (*it)->getType() << std::endl;
      found++;
    }
  }
  if(found == 0) {
    std::cout << "Your search returned no hits." << std::endl;
  }
}

//Print entire catalog
void POS::viewCat() {
  this->catalog->viewCatalog();
}
void POS::createProducts(std::ifstream& inFile) {
  inFile.open("../data/menu.txt");
  if (!inFile) {
    std::cout << "Unable to open file";
    exit(1); // terminate with error
  }

  std::string s_id, s_type, s_desc, s_ingred, s_organic, s_stocked;
  int i_id, i_stocked;
  bool i_organic;
  // std::cout << "ID\t\t\tType\t\t\tDesc\t\t\tIngred\tOrganic" << std::endl;
  // std::cout << "----------------------------------------------------------" << std::endl;
  std::string line;
  while(getline(inFile, line)) {
    std::stringstream linestream(line);

    getline(linestream, s_id,  ',' );
    getline(linestream, s_type,  ',' );
    getline(linestream, s_desc,  ',' );
    getline(linestream, s_ingred,  ',' );
    getline(linestream, s_organic,  ',' );
    getline(linestream, s_stocked,  ',' );

    i_id = stoi(s_id);
    i_stocked = stoi(s_stocked);
    if(s_organic == "true") {
      i_organic = true;
    }else{
      i_organic = false;
    }
    ProductDescription* prod = new ProductDescription(i_id, s_type, s_desc, s_ingred, i_organic, i_stocked);
    this->descriptions.push_back(prod);
    //std::cout <<  id << "\t\t\t" << type << "\t\t\t" << desc << "\t\t\t" << ingred << "\t" << organic << std::endl;
  }
  inFile.close();
}
//Need authorization to do this
void POS::createProducts(int productID, std::string type, std::string description, std::string ingredients, bool organic, int stocked) {
  ProductDescription* prod = new ProductDescription(productID, type, description, ingredients, organic, stocked);
  descriptions.push_back(prod);

}
void POS::addToCart(int id, int qty) {
  ProductDescription* desc = catalog->getDesc(id);
  cart->makeLineItem(desc, qty);
}
void POS::removeFromCart(int id, int qty) {
  ProductDescription* desc = catalog->getDesc(id);
  cart->removeLineItem(desc, qty);
}
void POS::makePayment(double cash) {
	order->makePayment(cash);
}
double POS::getCartTotal() {
  return cart->getCartTotal();
}
void POS::showCart() {
  std::list<SalesLineItem*> tmp = cart->getCartList();
  std::cout << std::fixed;
  std::cout << std::setprecision(2);
  std::cout << "Your total is $" << cart->getCartTotal() << std::endl;
  for(auto v : tmp)
    std::cout << v->getQty() << " X " << v->getName() << "   " << "$" << v->getSubTotal() << std::endl;
}
double POS::getChange() const {
  double chng = (order->getPay()->getAmount()) - (cart->getCartTotal());
  if(delivery) {
    chng -= 5;
  }
  cart->becomeOrdered();	//Clears out cart (deletes products in it)
  return chng;
}
void POS::simTrans() {
  std::cout << "Establishing connection";

  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << ".";
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << ".";
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Authorizing";
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << ".";
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "." << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "Payment successful.\n";
}
void POS::plugRule() {
  if(userAuthLevel < 2 || userAuthLevel > 3) {
    std::cout << "You dont have permission to do that.\n" << std::endl;
  }else{
    bool quit = false;
    do{
      std::cout << "What would you like to do?\n1: Fixed Discount\n2: Item Discount\n3: Exit" << std::endl;
      int menuchoice;
      do{
        std::cin >> menuchoice;
        std::cin.ignore();
        } while(menuchoice < 1 || menuchoice > 3);
      int prid, pct;
      switch(menuchoice) {
        case 1:
          std::cout << "\nEnter percentage for discount. [XXX%] (not decimal) ";
          double pcnt;
          std::cin >> pcnt;
          cart->setDiscount(pcnt);
          break;
        case 2:
          std::cout << "\nEnter item ID: ";
          std::cin >> prid;
          std::cout << "\nEnter discount percentage:";
          std::cin >> pct;
          for(listItr it = descriptions.begin(); it != descriptions.end(); it++) {
            if((*it)->getID() == prid) {
              (*it)->setDiscount(pct);
            }
          }
          std::cout << "Item: " << prid << " has successfully had a discount of " << pct << "%" << " set" << std::endl;
          break;
        case 3:
            quit = true;
          break;
        }
      } while(!quit);
  }
}