/**
 * Kent State University
 * CS 33901 Software Engineering
 * Fall 2017
 * Project #2
 * User Class
 * Author: Andrew Gast
 */

#include "mitchcloud.hpp"

/////////////////
// User Class
User::User() {
  this->accType = -1;
}
User::User(std::string user, std::string pass, std::string accT) {
  this->username = user;
  this->password = pass;
  this->accType = accT;
}
void User::changePriv(std::string accT) {
  this->accType = accT;
}
std::string User::getName() {
  return this->username;
}
std::string User::getPw() {
  return this->password;
}
std::string User::getPriv() {
  return this->accType;
}
void User::changeUn(std::string newUn) {
  this->username = newUn;
}
void User::changePw(std::string newPw) {
  this->password = newPw;
}


////////////////////////
// class User {
// private:
//   //customer = 0, clerk = 1, local manager = 2, cloud manager = 3, sales analyst = 4
//   int accType;
//   std::string username;
//   std::string password;
// public:
//   //constructor
//   User();
//   void changePriv();
//   void changeUn();
//   void changePw();
// };