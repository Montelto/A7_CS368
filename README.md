# A7_CS368
# Joseph McFarland
# 9072511679
# mcfarland3@wisc.edu

BattleShip is made up of Board.h, Ship.h, Point.h, BattleShip.cpp, and BattleShip.h.

Point.h creates a point with co-ordinates x and y within the board and a status (default EMPTY).
  It has other functions to print out and identify the point.

Ship.h "places" a ship on the board by changing the status of the ship's points to SHIP.
  Has other functions to identify the status of the ship.
  
Board.h crates a playing board of predetermined size with a boolean to hide the shipps on the board.
  Has additional functions to print out and manipulate point on the board.
  
make BattleShip
