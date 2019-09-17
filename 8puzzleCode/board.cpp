#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "board.h"

using namespace std;

/*======================================================================
empty constructor
========================================================================*/
board:: board() { 
}
/*======================================================================
set's up a gameboard such that it's connected to it's parent; 
========================================================================*/
board:: board( board* ptr, vector<vector<char> > b) { 
  gameboard = b; 
  gCost = ptr->getStepCost() + 1; 
  parent = ptr; 
  this->findEmptyPos(); 
  this->findStateHCost(); 
  fCost = gCost + hCost; 
}
/*======================================================================
set the gameboard from the user's input string
========================================================================*/
void board:: setGameboard(string numlist)
{
  parent = nullptr; 

  vector<char> row; 
  for (int i = 0 ; i < numlist.length() ; i++){
    if (numlist[i] >= '0' && numlist[i] <= '8') {
      if (numlist[i] == '0'){
        row.push_back(' '); 
      } else {
        row.push_back(numlist[i]); 
      }
      
      if (row.size() == 3){
        gameboard.push_back(row); 
        row.clear(); 
      }
    }
  }

  this->findEmptyPos(); 
  this->findStateHCost();   
  gCost = 0; 
  fCost = gCost + hCost; 
}
/*======================================================================
print's the object's board; 
========================================================================*/
void board:: printGameboard() const {
  for (int i = 0 ; i < gameboard.size() ;i++) {
     for (int j = 0; j < 3 ; j++){
       cout << gameboard[i][j]; 
       if ((j + 1) % 3 == 0) {
         cout << endl;
         cout << "----------" << endl;
       } else {
          cout << " | "; 
       }
     }
  }
}
/*======================================================================
returns the board's gameboard
========================================================================*/
vector<vector<char> >  board :: getGameboard() const {
  return (gameboard); 
}
/*======================================================================
returns the board's step cost
========================================================================*/
int board :: getStepCost() const {
  return (gCost);
}
/*======================================================================
returns the board's total cost
========================================================================*/
int board :: getTotalCost() const {
  return (fCost);
}
/*======================================================================
returns the board's heuristic cost
========================================================================*/
int board :: getHCost() const {
  return (hCost);
}
/*======================================================================
returns the board's empty spot
========================================================================*/
point board :: getEmptyPos() const {
  return (emptyPos); 
}
/*======================================================================
get's the object's parent
========================================================================*/
board* board:: getParent() const {
  return (parent);
}
/*======================================================================
finds the gameboard free spot
========================================================================*/
void board :: findEmptyPos() {
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3 ; j++){
      if (gameboard[i][j] == ' '){
        emptyPos.x = i; 
        emptyPos.y = j;
        break; 
      }
    }
  }
}
/*======================================================================
finds the boards heuristic Cost (manhattan function) 
========================================================================*/
void board ::findStateHCost() {
  hCost = 0; 
  point location; 
  for (int i = 0 ; i < 3 ; i++){
    for (int j = 0 ; j < 3 ; j ++){
      // the x location of a number is found by dividing by 3 
      // the y location of a number is found by modulos 3 
      // this formula prevents us from keeping track of the positions
        if (gameboard[i][j] == ' '){
            location.x = 0;
            location.y = 0;
        } else {
            location.x = (gameboard[i][j] - '0') / 3; 
            location.y = (gameboard[i][j] - '0') % 3; 
        }
        hCost+= abs(i - location.x) + abs(j - location.y);
    }
  }
}
