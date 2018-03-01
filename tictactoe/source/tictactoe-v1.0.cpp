/**
    Kent State University
    CS 33901 Software Engineering
    Fall 2017
    Project #1
    Simple Tic Tac Toe
    tictactoe-v0.9.cpp
    Source: http://paste4btc.com/enVArEWu
    Author #1: NVitanovic, https://www.youtube.com/user/NVitanovic
    Author #2: Andrew Gast
*/

#include "tictactoe.hpp"
#include <ctime>

//////////////////////////////////////////////
//~~~~~GameEngine Class
//Default constructor
//game can only start with 2 players
game::game(player plyr1, player plyr2) {
  isRunning = true;
  //Set player attributes for the game from the players created initially
  p1.setai(plyr1.getai());
  p1.setName(plyr1.getName());
  p1.setPiece(plyr1.getPiece());

  p2.setai(plyr2.getai());
  p2.setName(plyr2.getName());
  p2.setPiece(plyr2.getPiece());

  field.draw(p1, p2);
}

/////
//Functions
//execute turn for player, check for win/tie
//if win, adjust streaks and offer gamble/cashout
//if tie, reset all streaks
int game::takeTurn(player p, int pos) {
  if (field.isTaken(pos)) {
    std::cout << "That position is already taken, please pick again..." << std::endl;
    return 0; //indicating an unsuccessful turn
  } else {
    field.placePiece(p, pos); //place game piece
    //check win. if player won, update streak and wins
    if (field.checkWin()) {
      p.setWins(1);
      p.setStreak(p.getStreak() + 1);
      field.draw(p1, p2); //print updated game visuals
      if(p.getStreak() == 3) {  //offer cash out for $300k
        cashOut(p, 3);
      }else if(p.getStreak() == 6) { //offer cash out for $600k
        cashOut(p, 6);
      }else if(p.getStreak() == 9) { //offer cash out for $900k
        cashOut(p, 9);
      }else if(p.getStreak() == 10) { //game over, player wins
        std::cout << "Player " << p.getName() << " has won with 10 consecutive wins!" << std::endl;
        std::cout << "Game is over and will now terminate." << std::endl;
        isRunning = false;
      }else{ //no unique streak, turn over
        field.draw(p1, p2); //print updated game visuals
        return 1;
      }
    }else if (field.checkTie()) {
      //sets both player's streak to 0 on a tie game
      p1.setStreak(0);
      p2.setStreak(0);
      field.draw(p1, p2); //print updated game visuals
    }
  }
  return 1; //indicating a successful turn
}

//Determine whether the player cashes out their credits or continues their streak
//Computer is randomized
void game::cashOut(player p, int strk) {
  //computer cashOut (random)
  if (p.getai()) { //computer cashout
    srand(time(NULL));
    int num;
    num = rand() % 2 + 1;
    //1 = cashout, 2 = gamble
    if(strk < 9) {
      if(num == 1) {
        p.setCredits(strk*100000);
        if (p.getCredits() > 999999) {
          isRunning = false;
        }
        p.setStreak(0);
      }
    }else{
      if(num == 1) {
        p.setCredits(900000);
        if (p.getCredits() > 999999) {
          isRunning = false;
        }
        p.setStreak(0);
      }
    }
  }else{  //human cashout
    if (strk < 9){
      std::cout << "Would you like to keep your streak alive and go for $" << strk + 3 << "00k at " << strk + 3 << " wins?\nY/N?" << std::endl;
      char ans;
      std::cin >> ans;
      if (ans == 'n' || ans =='N') {
        p.setCredits(strk*100000);
        if (p.getCredits() > 999999) {
          std::cout << std::endl << "You have reached the max credits and have won the game. Congratulations!" << std::endl;
          isRunning = false;
        }
        p.setStreak(0);
      }
    }else{
      std::cout << "You're at 9 wins, 1 more and you win $1m and end the game. Would you like to continue your streak?\n Y/N?" << std::endl;
      char ans;
      std::cin >> ans;
      if (ans == 'n' || ans =='N') {
        p.setCredits(900000);
        if (p.getCredits() > 999999) {
          std::cout << std::endl << "You have reached the max credits and have won the game. Congratulations!" << std::endl;
          isRunning = false;
        }
        p.setStreak(0);
      }
    }
  }
}

//execute turn for computer player
int game::aiMoveGen(player p) {
  //generate random number from 0-8 (indicies of gameboard array)
  //check if the position is taken, if not, return that pos
  srand(time(NULL));
  int pos;
  pos = (rand() % 8) + 0;
  while (field.isTaken(pos)) {
    pos = (rand() % 8) + 0;
  }
  return pos;
}

//////////////////////////////////////////////
//~~~~~Player Class
//Default constructor
//create a new player for the game and assign base attributes
player::player() {
  isMachine = false;
  credits = 0;
  //Default name when none given
  name = "Player 1";
  // Random game piece when none selected
  srand(time(NULL));
  int num;
  num = rand() % 2 + 1;
  if (num == 1) {
    gamePiece = 'X';
  } else {
    gamePiece = 'O';
  }
}
//create new player when only name was input
player::player(std::string n) {
  isMachine = false;
  credits = 0;
  name = n;
  // Random game piece when none selected
  srand(time(NULL));
  int num;
  num = (rand() % 2) + 1;
  if (num == 1) {
    gamePiece = 'X';
  } else {
    gamePiece = 'O';
  }
}
//create new player when name and game piece given
player::player(std::string n, char gp) {
  isMachine = false;
  credits = 0;
  name = n;
  gamePiece = gp;
}
//create new player when only game piece given
player::player(std::string n, char gp) {
  isMachine = false;
  credits = 0;
  name = "Player 1";
  gamePiece = gp;
}
//create a computer player
player::player(int a, char gp) {
  isMachine = true;
  name = "Computer";
  //gp is Player 1's game piece
  //check Player 1's game piece and assign the opposite
  if (gp == 'X'){
    gamePiece = 'O';
  } else {
    gamePiece = 'X';
  }
}
/////
//Functions

//////////////////////////////////////////////
//~~~~~Board Class
//Default constructor
//creates new board and fills with numbers 1-9
board::board() {
  for (int i = 0; i < 9; i++){
    //convert int to char
    playField[i] = '0' + i + 1;
  }
  winner = '';
}
/////
//Functions
//draw the playing board on the screen
void board::draw(player p1, player p2) {
  std::cout << string(100, '\n');
  std::cout << "tictactoe v1.0" << std::endl;
  std::cout << std::endl << "\t\tSCORE" << std::endl;
  std::cout << p1.getName() << "\t  |\t" << p2.getName() << std::endl;
  std::cout << "wins: " << p1.getWins() << "\t\t  |\t" << "wins: " << p2.getWins() << std::endl;
  std::cout << "credits: $" << p1.getCredits() << "k" << "\t  |\t" << "credits: $" << p2.getCredits() << "k" << std::endl;
  std::cout << "streak: " << p1.getStreak() << "\t  |\t" << "streak: " << p2.getStreak() << std::endl << std::endl;
  int count = 0;
  for (int i = 0; i< 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cout << playField[count++] << " ";
    }
    std::cout << std::endl;
  }
}

//check to see if desired spot is taken
bool board::isTaken(int pos) {
  //convert int to char
  char cpos = '0' + pos;
  if (playField[pos-1] == cpos) {
    return false;
  }else {
    return true;
  }
}
//place the piece that was played on the board
void board::placePiece(player p, int pos) {
  //convert int to char
  char cpos = pos + '0';
  //int ipos = pos - '0';
  playField[pos-1] = p.getPiece();
}
//check the board for possible winning scenarios
bool board::checkWin() {
  //there are 8 possible winning lines in tictactoe
  //X wins
  if (playField[0] == 'X' && playField[1] == 'X' && playField[2] == 'X') {winner = 'X'; return true;}
  if (playField[3] == 'X' && playField[4] == 'X' && playField[5] == 'X') {winner = 'X'; return true;}
  if (playField[6] == 'X' && playField[7] == 'X' && playField[8] == 'X') {winner = 'X'; return true;}
  if (playField[0] == 'X' && playField[3] == 'X' && playField[6] == 'X') {winner = 'X'; return true;}
  if (playField[1] == 'X' && playField[4] == 'X' && playField[7] == 'X') {winner = 'X'; return true;}
  if (playField[2] == 'X' && playField[5] == 'X' && playField[8] == 'X') {winner = 'X'; return true;}
  if (playField[0] == 'X' && playField[4] == 'X' && playField[8] == 'X') {winner = 'X'; return true;}
  if (playField[6] == 'X' && playField[4] == 'X' && playField[2] == 'X') {winner = 'X'; return true;}
  //O wins
  if (playField[0] == 'O' && playField[1] == 'O' && playField[2] == 'O') {winner = 'O'; return true;}
  if (playField[3] == 'O' && playField[4] == 'O' && playField[5] == 'O') {winner = 'O'; return true;}
  if (playField[6] == 'O' && playField[7] == 'O' && playField[8] == 'O') {winner = 'O'; return true;}
  if (playField[0] == 'O' && playField[3] == 'O' && playField[6] == 'O') {winner = 'O'; return true;}
  if (playField[1] == 'O' && playField[4] == 'O' && playField[7] == 'O') {winner = 'O'; return true;}
  if (playField[2] == 'O' && playField[5] == 'O' && playField[8] == 'O') {winner = 'O'; return true;}
  if (playField[0] == 'O' && playField[4] == 'O' && playField[8] == 'O') {winner = 'O'; return true;}
  if (playField[6] == 'O' && playField[4] == 'O' && playField[2] == 'O') {winner = 'O'; return true;}
  //If none of those match, no wins
  return false;
}
//check if the board is tied
bool board::checkTie() {
  //if there is not a winner, check if there are vacant spots
  //if there are no vacant spots, the board is full and game is a tie
  if(!checkWin) {
    for (int i = 0; i < 9; i++) {
      //if any spots contain a number, the board is not full
      if (playField[i] == '0' + i + 1) {
        return false;
      }
    }
  }
  return true;
}

//////////////////////////////////////////////
//~~~~~Score Class
//Default constructor
//initializes all scores and streaks to zero
score::score() {
  p1Wins = 0;
  p1Streak = 0;
  p2Wins = 0;
  p2Streak = 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//NVitanovic Code, Original Source

/*
#include <iostream>
using namespace std;

char matrix[3][3] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
char player = 'X';

char Win()
{
    //first player
    if (matrix[0][0] == 'X' && matrix[0][1] == 'X' && matrix[0][2] == 'X')
        return 'X';
    if (matrix[1][0] == 'X' && matrix[1][1] == 'X' && matrix[1][2] == 'X')
        return 'X';
    if (matrix[2][0] == 'X' && matrix[2][1] == 'X' && matrix[2][2] == 'X')
        return 'X';

    if (matrix[0][0] == 'X' && matrix[1][0] == 'X' && matrix[2][0] == 'X')
        return 'X';
    if (matrix[0][1] == 'X' && matrix[1][1] == 'X' && matrix[2][1] == 'X')
        return 'X';
    if (matrix[0][2] == 'X' && matrix[1][2] == 'X' && matrix[2][2] == 'X')
        return 'X';

    if (matrix[0][0] == 'X' && matrix[1][1] == 'X' && matrix[2][2] == 'X')
        return 'X';
    if (matrix[2][0] == 'X' && matrix[1][1] == 'X' && matrix[0][2] == 'X')
        return 'X';

    //second player
    if (matrix[0][0] == 'O' && matrix[0][1] == 'O' && matrix[0][2] == 'O')
        return 'O';
    if (matrix[1][0] == 'O' && matrix[1][1] == 'O' && matrix[1][2] == 'O')
        return 'O';
    if (matrix[2][0] == 'O' && matrix[2][1] == 'O' && matrix[2][2] == 'O')
        return 'O';

    if (matrix[0][0] == 'O' && matrix[1][0] == 'O' && matrix[2][0] == 'O')
        return 'O';
    if (matrix[0][1] == 'O' && matrix[1][1] == 'O' && matrix[2][1] == 'O')
        return 'O';
    if (matrix[0][2] == 'O' && matrix[1][2] == 'O' && matrix[2][2] == 'O')
        return 'O';

    if (matrix[0][0] == 'O' && matrix[1][1] == 'O' && matrix[2][2] == 'O')
        return 'O';
    if (matrix[2][0] == 'O' && matrix[1][1] == 'O' && matrix[0][2] == 'O')
        return 'O';

    return '/';
}
int main()
{
    //Draw
    cout << string( 100, '\n' );
    cout << "TicTacToe v0.9" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    while (1)
    {
        //Input
        int a;
        cout << "Press the number of the field: ";
        cin >> a;

        if (a == 1)
            matrix[0][0] = player;
        else if (a == 2)
            matrix[0][1] = player;
        else if (a == 3)
            matrix[0][2] = player;
        else if (a == 4)
            matrix[1][0] = player;
        else if (a == 5)
            matrix[1][1] = player;
        else if (a == 6)
            matrix[1][2] = player;
        else if (a == 7)
            matrix[2][0] = player;
        else if (a == 8)
            matrix[2][1] = player;
        else if (a == 9)
            matrix[2][2] = player;

        //Draw
        cout << string( 100, '\n' );
        cout << "tictactoe v0.9" << endl;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }

        if (Win() == 'X')
        {
            cout << "X wins!" << endl;
            break;
        }
        else if (Win() == 'O')
        {
            cout << "O wins!" << endl;
            break;
        }

        //TogglePlayer
        if (player == 'X')
            player = 'O';
        else
            player = 'X';
    }
    return 0;
}
*/
