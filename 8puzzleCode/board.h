#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <queue> 
#include "point.h"

using namespace std; 

class board {
    private: 
      int fCost;
      int gCost; 
      int hCost;
      vector<vector<char> > gameboard; 
      point emptyPos;
      board* parent;

    public:
      // empty constructor defines the new object 
      // board(board*, vector) constructor connects board to it's parent
      board();
      board(board*, vector<vector<char> >); 
      // gameboard functions
      void setGameboard(string); 
      void printGameboard() const;
      vector<vector<char> > getGameboard() const;
      // f(n) function
      int getTotalCost() const; 
      // g(n) function
      int getStepCost() const;
      // h(n) functions
      void findStateHCost();  
      int getHCost() const; 
      // free space function
      void findEmptyPos();
      point getEmptyPos() const;
      // get's parent
      board* getParent() const; 
};


#endif