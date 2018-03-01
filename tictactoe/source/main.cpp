/**
 *  @file main.cpp
 *  TicTacToe
 *
 *  @author Andrew Gast.
 *  Copyright 2017 Kent State University. All rights reserved.
 *
 *  Requires main.cpp first, followed by other files.
 *
 */

 #include "tictactoe.hpp"

 int main(int argc, char *arg[v]) {
   std::cout << "Welcome to TicTacToe!\n";
   std::cout << "1 Player or 2 Players?" << std::endl;
   int players = 0;
   std::cin >> players;
   //guarantee correct input from user
   while (players > 2 || players < 1) {
     std::cout << "\nInvalid input. Please enter 1 or 2." << std::endl;
     std::cin >> players;
   }

   if(players = 1) { //create 1 human player and 1 computer player
     std::string n;
     char pc;
     std::cout << "Please enter name for player 1...\n";
     std::cin >> n;
     std::cout << "\nX or O?\n";
     std::cin >> pc;
     pc = toupper(pc);
     player player1(n, pc);
     player player2(1, player1.getPiece());
   }else{ //create 2 human players
     std::string n1;
     char pc1;
     std::cout << "Please enter name for player 1...\n";
     std::cin >> n1;
     std::cout << "\nX or O?\n";
     std::cin >> pc1;
     pc1 = toupper(pc1);
     player player1(n1, pc1);

     std::string n2;
     char pc2;
     std::cout << "Please enter name for player 2...\n";
     std::cin >> n2;
     //ensure both players dont pick the same gamepiece
     if(player1.getPiece() == 'X') {
       pc2 = 'O';
     }else{
       pc2 = 'X';
     }
     player player2(n2, pc2);
   }

  /////////Start the game
  game ttt(player1, player2);
  //keep track of turns
  int p1turns = 0;
  int p2turns = 0;
  while (ttt.isRunning) {
    if(p2turns == p1turns) { //it is now player 1s turn
      std::cout << "Select a location " << player1.getName() << std::endl;
      int pos;
      do{
        std::cin >> pos;
        //ensure nothing other than 1-9 is entered
        while (pos > 9 || pos < 1) {
          std::cout << "\nInvalid input. Please enter 1-9." << std::endl;
          std::cin >> pos;
        }
        //if the spot chosen is occupied, select again
        if(ttt.field.isTaken(pos)){
          std::cout << "That spot is taken. Try again." << std::endl;
        }
      }while(ttt.field.isTaken(pos));
      //place piece at position
      ttt.takeTurn(ttt.p1, pos);
      ++p1turns;
    }else{ //it is now player 2s turn
      if(ttt.p2.getai()) { //2nd player is computer
        ttt.takeTurn(ttt.p2, ttt.aiMoveGen(p2));
        ++p2turns;
      }else{ //player 2 is human
        std::cout << "Select a location " << player2.getName() << std::endl;
        int pos;
        do{
          std::cin >> pos;
          //ensure nothing other than 1-9 is entered
          while (pos > 9 || pos < 1) {
            std::cout << "\nInvalid input. Please enter 1-9." << std::endl;
            std::cin >> pos;
          }
          //if the spot chosen is occupied, select again
          if(ttt.field.isTaken(pos)){
            std::cout << "That spot is taken. Try again." << std::endl;
          }
        }while(ttt.field.isTaken(pos));
        //place piece at position
        ttt.takeTurn(ttt.p2, pos);
        ++p2turns;
      }
    }
  }
   return 0;
 }
