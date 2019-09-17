#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include "board.h"
using namespace std; 

typedef vector<vector<char> > gameboard; 
typedef vector<gameboard> states; 


string getNumericalList();
bool validNumericalList(string); 
vector<point> findBoardMoves(point); 
point nextMove(int, point); 
states newChildren(vector<point> , gameboard, point);
void printListOfMoves (board* ptr);

/*====================================================================
Allows the priority_queue to put board with lowest Cost at the front
======================================================================*/
struct Comparison 
{ 
    bool operator()(const board b1,const board b2)
    { 
        return (b1.getTotalCost() > b2.getTotalCost()); 
    } 
};

int main() {

  set <gameboard> previousBoards;  
  priority_queue<board ,vector<board> , Comparison> pq; 
  string numericalList = getNumericalList(); 
  while (!validNumericalList(numericalList)){
    cout << "invalid!" << endl; 
    cout << "enter start state: "; 
    getline(cin,numericalList); 
  } 
  cout << endl; 

  board begPuzzle; 
  begPuzzle.setGameboard(numericalList);
  pq.push(begPuzzle); 
  previousBoards.insert(begPuzzle.getGameboard()); 

  while (!pq.empty()){

    board *current = new board; 
    *current = pq.top(); 
    pq.pop();  
    
    if (current->getHCost() == 0){
      printListOfMoves (current);
      cout << "Number of steps: " << current->getStepCost();  
      break; 
    }

    vector<point> nextMoves = findBoardMoves(current->getEmptyPos()); 
    states children = newChildren(nextMoves,
                      current->getGameboard(),         
                      current->getEmptyPos());

    for (int i = 0; i < children.size() ; i++ ){
        board son(current,children[i]); 
        if (previousBoards.find(son.getGameboard()) == previousBoards.end()){
            previousBoards.insert(son.getGameboard()); 
            pq.push(son); 
        }  
    }
  }
  
}
/*====================================================================
User initializes the start state as numerical list 
======================================================================*/
string getNumericalList(){
  
  string numList; 
  cout << "enter start state: "; 
  getline(cin, numList); 
  
  return (numList); 
}
/*====================================================================
Validates the user's numerical list
======================================================================*/
bool validNumericalList(string numList) {
 
  bool valid = false;
  string sortedValues = "012345678"; 
  string values;
  
  for (int i = 0; i < numList.length() ;i++){
    if (numList[i] == ' '){
      continue; 
    } else if (numList[i] < '0' && numList[i] > '8') {
      return (valid); 
    } else {
      values+=numList[i]; 
    }
  }
  valid = true; 
  sort(values.begin(),values.end()); 

  return (valid && (sortedValues.compare(values) == 0));
}
/*====================================================================
find's which way the empty location can move
======================================================================*/
vector<point> findBoardMoves (point blank){
  
  vector <point> nextMoves; 
  int key; 
  point p; 
  if (blank.x > 0 ){
    // can move up, key is 1
    key = 1; 
    p = nextMove(key, blank); 
    nextMoves.push_back(p); 
  }
  if (blank.x < 2){
    // can move down, key is 2
    key = 2; 
    p = nextMove(key, blank); 
    nextMoves.push_back(p);
  }
  if (blank.y < 2){
    // can move right, key is 3
    key = 3; 
    p = nextMove(key, blank); 
    nextMoves.push_back(p);
  }
  if (blank.y > 0){
    // can move left, key is default
    key = 4; 
    p = nextMove(key, blank); 
    nextMoves.push_back(p);
  }

  return (nextMoves); 
}
/*====================================================================
returns a move the user can make using the key from findBoardMoves
======================================================================*/
point nextMove(int key,point blank){
  point move; 
  if (key == 1 ){
      move.x = blank.x - 1; 
      move.y = blank.y;
  } else if (key == 2){
      move.x = blank.x + 1; 
      move.y = blank.y;
  } else if (key == 3){
      move.x = blank.x; 
      move.y = blank.y + 1; 
  } else {
      move.x = blank.x;
      move.y = blank.y - 1; 
  }

  return (move); 
}
/*====================================================================
creates the children from the possible moves
======================================================================*/
states newChildren(vector<point> p, gameboard g, point empty){
  states list;  
  point swapPoint; 
  gameboard temp; 
  for (int i = 0 ; i < p.size() ;i++){
    temp = g; 
    swapPoint = p[i]; 
    swap(temp[swapPoint.x][swapPoint.y], temp[empty.x][empty.y]); 
    list.push_back(temp); 
  }
  return(list); 
}
/*====================================================================
Print's out the path to the solution 
======================================================================*/
void printListOfMoves (board* ptr){
  
  vector<board*> moves; 

  while (ptr){
    moves.push_back(ptr); 
    ptr = ptr->getParent(); 
  }

  while (!moves.empty()){
    board* printboard = new board; 
    printboard = moves.back(); 
    
    if (printboard->getStepCost() != 0 ){
      cout << "step number: " << printboard->getStepCost(); 
      cout << endl; 
    }
    
    printboard->printGameboard(); 
    cout << endl; 
    moves.pop_back(); 
  }

}