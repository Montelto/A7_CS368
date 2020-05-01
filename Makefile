# A7_368
# Joseph McFarland
# 9072511679
# mcfarland3@wisc.edu

CXX = g++
CXXFLAGS = -Wall -g

BattleShip.o: BattleShip.cpp BattleShip.h Board.h Ship.h Point.h
	$(CXX) $(CXXFLAGS) -c BattleShip.cpp

clean:
	-rm BattleShip.o
	-rm BattleShip

SummarizeGrades: demo.o
	$(CXX) $(CXXFLAGS) -o BattleShip BattleShip.o
