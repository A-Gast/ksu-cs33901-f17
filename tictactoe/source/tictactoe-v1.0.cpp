/**
    Kent State University
    CS 33901 Software Engineering
    Fall 2017
    Project #1
    Simple Tic Tac Toe
    tictactoe-v1.0.cpp
    Source: http://paste4btc.com/enVArEWu
    Author #1: NVitanovic, https://www.youtube.com/user/NVitanovic
    Author #2: Andrew Gast
*/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

//Player class
class player {
public:
  player();
  int stats[3];   //0=credits, 1=wins, 2=streak
  int turns;
  char piece;
  bool ai;
};
//Board class
class board {
public:
  int ties;
  board();
  bool isRunning;
  char win();
  bool tie();
  void draw(int player1[3], int player2[3]);
  void reset();
  void place(char piece, int a);
  bool isTaken(int a);
  void cashOut(bool ai, int sts[3], int strk);

private:
  char matrix[3][3];
};
board::board() {
  isRunning = true;
  ties = 0;
  reset();
}
char board::win() {
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
bool board::tie() {
  //check if entire board is filled
  for (int i = 1; i < 10; i++) {
    if (isTaken(i) == false){
      return false;
    }
  }
  return true;
}
void board::draw(int player1[3], int player2[3]) {
  //player[]: 0=credits 1=wins 2=streak
  std::cout << std::string( 100, '\n' );
  std::cout << "\tTicTacToe v1.0" << std::endl;
  std::cout << "Player 1\t\tPlayer 2" << std::endl;
  std::cout << "credits: " << player1[0];
  if (player1[0] > 0) {
    std::cout << "00k";
  }
  std::cout << "\t\tcredits: " << player2[0];
  if (player2[0] > 0) {
    std::cout << "00k"<< std::endl;
  }else{std::cout << std::endl;}
  std::cout << "wins: " << player1[1] << "\t\t\twins: " << player2[1] << std::endl;
  std::cout << "streak: " << player1[2] << "\t\tstreak: " << player2[2] << std::endl;
  std::cout << "\tties: " << ties << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
void board::reset() {
  int x = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix[i][j] = '0' + x++;
    }
  }
}
void board::place(char piece, int a) {
  if (a == 1)
    matrix[0][0] = piece;
  else if (a == 2)
    matrix[0][1] = piece;
  else if (a == 3)
    matrix[0][2] = piece;
  else if (a == 4)
    matrix[1][0] = piece;
  else if (a == 5)
    matrix[1][1] = piece;
  else if (a == 6)
    matrix[1][2] = piece;
  else if (a == 7)
    matrix[2][0] = piece;
  else if (a == 8)
    matrix[2][1] = piece;
  else if (a == 9)
    matrix[2][2] = piece;
}
bool board::isTaken(int a) {
  //check the matrix to see if the spot is taken
  if (a == 1) {
    return (matrix[0][0] != '1');
  }else if (a == 2) {
    return (matrix[0][1] != '2');
  }else if (a == 3) {
    return (matrix[0][2] != '3');
  }else if (a == 4) {
    return (matrix[1][0] != '4');
  }else if (a == 5) {
    return (matrix[1][1] != '5');
  }else if (a == 6) {
    return (matrix[1][2] != '6');
  }else if (a == 7) {
    return (matrix[2][0] != '7');
  }else if (a == 8) {
    return (matrix[2][1] != '8');
  }else if (a == 9) {
    return (matrix[2][2] != '9');
  }
  return true;
}
void board::cashOut(bool ai, int sts[3], int strk) {
  int a;
  if (ai) { //if player is computer, randomize cash out selection
    int rnd;
    srand(time(NULL));
    a = rand() % 2 + 1;
    //ans[0] = '0' + rnd;
  }else { //if player is human, prompt for input
    std::cout << "Would you like to stop and cash out $" << strk << "00k [1], or continue your streak? [2]" << std::endl;
    do {
      char ans[6];
      std::cin >> ans;
      std::string str = ans;
      if (str == "quit") {
        isRunning = false;
        return;
      }
      a = ans[0] - '0';
    }while(a < 1 || a > 2);
  }
  if (a == 1) { //add credits and reset streak if cashout is selected
    sts[0] = sts[0] + (strk);
    sts[2] = 0;
  }
}

//create player by setting stats to 0
player::player() {
  for (int i = 0; i < 3; i++) {
    stats[i] = 0;
  }
  turns = 0;
  ai = false;
}
/////////////////////
//Game initialization
int main() {
  //create players and set their pieces.
  player player1, player2;
  player1.piece = 'X';
  player2.piece = 'O';
  board game;

  std::cout << "Single player or 2? (1/2)" << std::endl;
  int numplyrs;
  std::cin >> numplyrs;
  //can only enter 1 or 2
  while (numplyrs > 2 || numplyrs < 1) {
    std::cin >> numplyrs;
  }
  if (numplyrs == 1) {
    player2.ai = true;
  }

  while (game.isRunning) {
    //Draw
    game.draw(player1.stats, player2.stats);
    //if player 2 is a computer player, randomly choose spot
    int a;
    if ((player2.turns < player1.turns) && player2.ai) {
      do{
        int rnd;
        srand(time(NULL));
        a = rand() % 9 + 1;
      }while(game.isTaken(a));
    }else{ //human players turn taking sequence
      //ensure input is valid between 1-9
      //and that the spot isnt taken
      std::cout << "Press the number of the field: ";
      do {
        char inpt[25];
        std::cin >> inpt;
	std::string str = inpt;
	if (str == "quit") {
	  game.isRunning = false;
	  return 0;
	}
        a = inpt[0] - '0';
      }while(game.isTaken(a));
    }

    //if player 2 has same amount of turns as player 1, 2 went last
    if (player2.turns == player1.turns) {
      std::cout << "Player 1's turn." << std::endl;
      game.place(player1.piece, a);
      ++player1.turns;
    }else{ //otherwise it is player 2s turn.
      std::cout << "Player 2's turn." << std::endl;
      game.place(player2.piece, a);
      ++player2.turns;
    }
    //Check for a game winner: X
    if (game.win() == 'X') {
      player1.stats[1] = player1.stats[1] + 1;
      player1.stats[2] = player1.stats[2] + 1;
      player2.stats[2] = 0;
      game.draw(player1.stats, player2.stats);
      std::cout << "X wins!" << std::endl;
      game.reset();
      player1.turns = 0;
      player2.turns = 0;
      //0=credits, 1=wins, 2=streak
      if (player1.stats[2] == 3) { //3 streak, option to cash out $300k
        game.cashOut(player1.ai, player1.stats, 3);
      }else if (player1.stats[2] == 6) { //6 streak, option to cash out $600k
        game.cashOut(player1.ai, player1.stats, 6);
      }else if (player1.stats[2] == 9) { //9 streak, option to cash out $900k
        game.cashOut(player1.ai, player1.stats, 9);
      }else if (player1.stats[2] == 10) {
        std::cout << "Player 1 automatically wins $1m and won the game. Congrats!!" << std::endl;
        game.isRunning = false;
        return 0;
      }
      if (player1.stats[0] >= 10) {
        std::cout << "Player 1 wins with over $1m credits!!" << std::endl;
        return 0;
      }
      //check for a game winner: O
    }else if (game.win() == 'O') {
      player2.stats[1] = player2.stats[1] + 1;
      player2.stats[2] = player2.stats[2] + 1;
      player1.stats[2] = 0;
      game.draw(player1.stats, player2.stats);
      std::cout << "O wins!" << std::endl;
      game.reset();
      player1.turns = 0;
      player2.turns = 0;
      //0=credits, 1=wins, 2=streak
      if (player2.stats[2] == 3) { //3 streak, option to cash out $300k
        game.cashOut(player2.ai, player2.stats, 3);
      }else if (player2.stats[2] == 6) { //6 streak, option to cash out $600k
        game.cashOut(player2.ai, player2.stats, 6);
      }else if (player2.stats[2] == 9) { //9 streak, option to cash out $900k
        game.cashOut(player2.ai, player2.stats, 9);
      }else if (player2.stats[2] == 10) {
        std::cout << "Player 2 automatically wins $1m and won the game. Congrats!!" << std::endl;
        game.isRunning = false;
        return 0;
      }
      if (player2.stats[0] >= 10) {
        std::cout << "Player 2 wins with over $1m credits!!" << std::endl;
        return 0;
      }
      //check for a game tie
    }else if (game.tie()) {
      game.ties ++;
      player1.stats[2] = 0;
      player2.stats[2] = 0;
      game.draw(player1.stats, player2.stats);
      std::cout << "Tie game!" << std::endl;
      game.reset();
      player1.turns = 0;
      player2.turns = 0;
    }
    if (game.isRunning == false) {
      return 0;
    }
  }
  return 0;
}
