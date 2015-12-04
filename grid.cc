#include "grid.h"
#include <iostream>

using namespace std;

//Default constructor
Grid::Grid():gridSize(0), td(NULL) ,theGrid(NULL), theWindow(NULL) {
}

// Frees the theGrid field.
void Grid::clearGrid() {
   for(int i = 0; i < gridSize; i++) {
      delete [] theGrid[i];
   }
   delete [] theGrid;
}

Grid::~Grid() {
   clearGrid();
   delete td;
   delete theWindow;
}


bool Grid::isWon() {
   return td->isFilled();
}

void Grid::init(int n) {
   gridSize = n;
   if(td == NULL) {
      TextDisplay *tempDis= new TextDisplay(n);
      td = tempDis;
   }
   if(theWindow == NULL) {
      theWindow = new Xwindow;
   }
   int d = 500 / gridSize;
   if(theGrid == NULL) {
      theGrid = new Cell* [n];
      for(int i = 0; i < n; i++) {
         theGrid[i] = new Cell[n];
         for(int j = 0; j < n; j++) {
            theGrid[i][j].setCoords(i,j);
            theGrid[i][j].setDisplay(td);
            theGrid[i][j].setState(0);
            theGrid[i][j].setCoords(i,j,i,j,d,d,theWindow);
         }
      }
   }
   
   //this part is to add neighbours to each cell in the grid
   for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
         if(i - 1 >= 0) {
            theGrid[i][j].addNeighbour(&(theGrid[i-1][j]));
         }
         if(i + 1 < n) {
            theGrid[i][j].addNeighbour(&(theGrid[i+1][j]));
         }
         if(j - 1 >= 0) {
            theGrid[i][j].addNeighbour(&(theGrid[i][j-1]));
         }
         if(j + 1 < n) {
            theGrid[i][j].addNeighbour(&(theGrid[i][j+1]));
         }
      }
   }
}

// Notify Cell (0,0) of the change to new state: state 
void Grid::change(const int & state) {
   theGrid[0][0].notify(state);
}

//set the state for r,c to state
void Grid::init(int r, int c, int state) {
   theGrid[r][c].setState(state);
}

//"output" operator overloading
std::ostream& operator<<(std::ostream &out, const Grid &g) {
   out << *(g.td);
   return out;
}

