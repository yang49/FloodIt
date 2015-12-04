#include "textdisplay.h"

using namespace std;

//one arg constructor where the parameter is the gridSize
TextDisplay::TextDisplay(int n):gridSize(n) {
      theDisplay = new char * [n];
      for(int i = 0; i < n; i++) {
         theDisplay[i] = new char [n];
         for(int j = 0; j < n; j++) {
            theDisplay[i][j] = '0';
         }
   }
   for(int i = 0;i < 5; i++) {
      colourCount[i] = 0;
   }
   colourCount[0] = gridSize * gridSize;
}

void TextDisplay::notify(int r, int c, char ch) {
      int pre = theDisplay[r][c] - '0';
      colourCount[theDisplay[r][c] - '0']--;
      theDisplay[r][c] = ch;
      colourCount[theDisplay[r][c] - '0']++;
}

//
bool TextDisplay::isFilled() {
   for(int i = 0; i < 5; i++) {
      if(colourCount[i] == gridSize * gridSize) {
         return true;
      }
   }
   return false;
}


//Desctructor
TextDisplay::~TextDisplay() {
   for(int i = 0; i < gridSize; i++) {
         delete [] theDisplay[i];
   }
   delete [] theDisplay;
}

std::ostream& operator<<(std::ostream &out, const TextDisplay &td) {
   for(int i = 0;i < td.gridSize; i++) {
      for(int j = 0;j < td.gridSize; j++) {
         out << td.theDisplay[i][j];
      }
      out << "\n";
   }
   return out;
}
