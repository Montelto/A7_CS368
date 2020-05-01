//
// Joseph McFarland
// 9072511679
// mcfarland3@wis.edu
// https://canvas.wisc.edu/courses/188843/files for slides
// Made in CLion with commits to GitHub
//

#include "BattleShip.h"

int main()
{
  default_random_engine rand(std::random_device{}());
  char rerun;
  do
    {
      initGame();
      placeShips(rand);
      playGame(rand);
      cout << "Would you like to play again? (y/n) ";
      cin >> rerun;
    } while (rerun == 'y' || rerun == 'Y');
  return 0;
}

void initGame()
{
  pBoard = Board<MAX_X,MAX_Y>(false);
  cBoard = Board<MAX_X,MAX_Y>(true);
  player.empty();
  computer.empty();
}

void placeShips(default_random_engine &rand)
{
  uniform_int_distribution<unsigned> randX(0,MAX_X-1);
  uniform_int_distribution<unsigned> randY(0,MAX_Y-1);
  bernoulli_distribution randDir;
  auto s = ships.begin();
  while(s != ships.end())
    {
      try
        {
          Ship<MAX_X,MAX_Y> toAdd(s->name, {randX(rand),randY(rand)}, s->len,
                                  randDir(rand) ? VERTICAL : HORIZONTAL, cBoard);
          computer.push_back(toAdd);
          ++s;
        }
      catch (std::out_of_range &) { }
      catch (invalid_argument &) { }
    }

  cout << "Place your ships:\n";
  s = ships.begin();
  while(s != ships.end())
    {
      unsigned row{0};
      char col{'A'}, dir{'v'};
      cout << "Enter row [1," << MAX_Y << "] and column [A," << Point<MAX_X,MAX_Y>::xToChar(MAX_X-1) << "] "
           << "of " << s->name << ": ";
      cin >> row >> col;
      col = toupper(col);
      cout << "Vertical or horizontal? (v/h) ";
      cin >> dir;
      if(cin.fail())
        {
          cin.clear(); 
          cin.ignore();
          continue;
        }
      try
        {
          Ship<MAX_X,MAX_Y> toAdd(s->name, {col,row-1}, s->len,
                                  (dir == 'v' || dir == 'V') ? VERTICAL : HORIZONTAL, pBoard);
          player.push_back(toAdd);
          ++s;
        }
      catch (out_of_range &)
        {
          cout << "Oops, that ship would be out-of-bounds!\n";
        }
      catch (invalid_argument &)
        {
          cout << "Oops, there is a ship there already!\n";
        }
    }
}

void playGame(default_random_engine &rand)
{
  uniform_int_distribution<unsigned> randX(0,MAX_X-1);
  uniform_int_distribution<unsigned> randY(0,MAX_Y-1);
  bool playerLost{false};
  bool computerLost{false};

  printBoards();
  
  do
    {
      unsigned row{0};
      char col{'A'};
      cout << "Take a shot: Enter row [1," << MAX_Y << "] and column [A,"
           << Point<MAX_X,MAX_Y>::xToChar(MAX_X-1) << "]: ";
      cin >> row >> col;
      if(cin.fail())
        {
          cin.clear(); 
          cin.ignore();
          continue;
        }
      col = toupper(col);
      try
        {
          Point<MAX_X,MAX_Y> shot{col,row-1};
          doShot(shot,computer,cBoard);
        }
      catch(out_of_range &)
        {
          cout << "Oops, shot is out-of-bounds.\n";
          continue;
        }
      cout << "Computer is shooting... ";
      bool validPt{false};
      do
        {
          try
            {
              Point<MAX_X,MAX_Y> shot{randX(rand),randY(rand)};             
              validPt = true;
              doShot(shot, player, pBoard);
            }
          catch(out_of_range &) {}
        }
      while(!validPt);
      printBoards();
    }
  while(!(playerLost = checkLost(player)) && !(computerLost = checkLost(computer)));
  if(playerLost && computerLost)
    cout << "Tie game!";
  else if(playerLost)
    cout << "Oh no, you lost! Better luck next time!";
  else
    cout << "You won! Congratulations!";
  cout << "\n";
}

bool checkLost(std::vector<Ship<MAX_X,MAX_Y>> &ships)
{
  for(auto s: ships)
    {
      if(!s.isSunk()) return false;
    }
  return true;
}

void doShot(Point<MAX_X,MAX_Y> &shot, std::vector<Ship<MAX_X,MAX_Y>> &ships, Board<MAX_X,MAX_Y> &board)
{
  for(auto s: ships)
    {
      if(s.isHit(shot))
        {
          cout << shot << " is a hit!\n";
          if(s.isSunk()) {
            cout << s.getName() << " has been sunk!\n";
          }
          return;
        }
    }
  board.setStatus(shot, MISS);
  cout << shot << " is a miss.\n";
}

void printBoards()
{
  cout << "Computer:\n" << cBoard << "Player:\n" << pBoard;
}
