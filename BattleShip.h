//
// Joseph McFarland
// 9072511679
// mcfarland3@wis.edu
// https://canvas.wisc.edu/courses/188843/files for slides
// Made in CLion with commits to GitHub
//

#ifndef BATTLESHIP_MAIN_H
#define BATTLESHIP_MAIN_H

#include <random>
#include <vector>
#include "Point.h"
#include "Ship.h"
#include "Board.h"
#include <stdexcept>
using namespace std;

constexpr unsigned MAX_X{10};
constexpr unsigned MAX_Y{10};

vector<Ship<MAX_X,MAX_Y>> player;
vector<Ship<MAX_X,MAX_Y>> computer;
Board<MAX_X,MAX_Y> pBoard(false);
Board<MAX_X,MAX_Y> cBoard(true);

struct DefShip {
  unsigned len;
  string name;
};
  
vector<DefShip> ships {{2, "destroyer"},
                            {3, "cruiser"},
                            {3, "submarine"},
                            {4, "battleship"},
                            {5, "carrier"}};

void initGame();
void placeShips(default_random_engine &rand);
void playGame(default_random_engine &rand);
bool checkLost(vector<Ship<MAX_X,MAX_Y>> &ships);
void doShot(Point<MAX_X,MAX_Y> &shot, vector<Ship<MAX_X,MAX_Y>> &ships, Board<MAX_X,MAX_Y> &board);
void printBoards();

#endif
