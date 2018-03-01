/**
 *  @file tictactoe.hpp
 *
 *  @author Andrew Gast.
 *  Copyright 2017 Kent State University. All rights reserved.
 *
 */

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <iostream>
#include <string>

//////////////////////////////////////////////
//Game Class
class game {
  //friend class player;
private:
  bool isRunning;
  board field;
  player p1;
  player p2;

public:
  //Constructors
  game(player plyr1, player plyr2);

  //Functions
  int takeTurn(player p, int pos);
  void cashOut(player p, int strk);
  //for ai move,
  //takeTurn(p2,aiMoveGen(p2));
  int aiMoveGen(player p);
};

//////////////////////////////////////////////
//Player Class
class player {
private:
  bool isMachine;
  std::string name;
  char gamePiece;
  int wins;
  int streak;
  int credits;
public:
  //Constructors
  player();                         //user does not input anything
  player(std::string n);            //user only inputs name
  player(char gp);                  //user only inputs game piece
  player(std::string n, char gp);   //user inputs name and game piece
  player(bool ai, char gp);         //indicates creation of computer player

  //Functions
  //accessors
  bool getai() {return isMachine;};
  std::string getName() {return name;};
  char getPiece() {return gamePiece;};
  int getWins() {return wins;};
  int getStreak() {return streak;};
  int getCredits() {return credits;};
  //modifiers
  void setai(bool ai) {isMachine = ai;};
  void setName(std::string n) {name = n;};
  void setPiece(char pc) {gamePiece = pc;};
  void setWins(int w) {wins = wins + w;};
  void setStreak(int s) {streak = s;};
  void setCredits(int c) {credits = credits + c;};
};

//////////////////////////////////////////////
//Board Class
class board {
private:
  char playField[9];
  char winner;
public:
  //Constructors
  board();

  //Functions
  void draw(player p1, player p2);
  bool isTaken(int pos);
  void placePiece(player p, int pos);
  bool checkWin();
  bool checkTie();
};

/*
//////////////////////////////////////////////
//Score Class
class score {
private:
  int wins;
  int streak;
public:
  //Constructors
  score();

  //Functions
  //accessors
  int getWins() {return wins;};
  int getStreak() {return streak;};
  //mutators
  void setWins(int w) {wins = wins + w;};
  void setStreak(int s) {streak = s;};
};
*/
#endif
