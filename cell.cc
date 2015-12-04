#include "cell.h"
#include <string>

using namespace std;

//default constructor for Cell
Cell::Cell():state(0),prevState(0),numNeighbours(2), r(0), c(0),
             x(0), y(0), width(0), height(0), td(NULL) {
   for(int i = 0; i < maxNeighbours; i++) {
      neighbours[i] = NULL;
   }
}

//getter for private state
int Cell::getState() {
   //cout << "getting -> " << r << " , " << c << endl;
   return state;
}

//setter for private state
void Cell::setState(const int& change) {
   if(change != state) {
      prevState = state;
      state = change;
      this->draw();
      this->notifyDisplay();
   }
}

//setter for private co-ordinates of cell
void Cell::setCoords(const int r, const int c) {
   this->r = r;
   this->c = c;
}

void Cell::setCoords(int r, int c, int x, int y, int width, int height, Xwindow *w) {
   this->r = r;
   this->c = c;
   this->x = c;
   this->y = r;
   this->width = width;
   this->height = height; 
   this->window = w;
}
//setter for TextDisplay
void Cell::setDisplay(TextDisplay * t) {
   td = t;
}

//add a neighbouring cell
void Cell::addNeighbour(Cell *neighbour) {
   for(int i = 0; i < maxNeighbours; i++) {
      if(neighbours[i] == NULL) {
         neighbours[i] = neighbour;
         break;
      }
   }
}

//first notify method
void Cell::notify(const int & change) {
   this->setState(change);
   this->notify(this->state, this->prevState);
}
//second notify method for Neighbour
void Cell::notify(const int & current, const int & previous) {
   for(int i = 0; i < maxNeighbours; i++) {
      if(neighbours[i] != NULL) {
         if(previous == neighbours[i]->getState()) {
            neighbours[i]->setState(current);
            neighbours[i]->notify(current, previous);
         }
      }
   }
}

//notify the TextDisplay of the change
void Cell::notifyDisplay() {
   td->notify(r, c, '0' + state);
}

//draw
void Cell::draw(void) {
   //fillRectangle(int x, int y, int width, int height, int colour=Black)
   window->fillRectangle(x*width, y*height, width, height, state);
}
