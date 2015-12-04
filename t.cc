#include "grid.h"
#include "textdisplay.h"
#include "cell.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(void) {
   Grid g;
   cout << "First line\n";
   g.init(30);
   //g.init(2, 2, 4);
   //g.init(2, 2, 0);
   //cout << "1\n";
   if(g.isWon()) {
      cout << "Won" << endl;
   }
   cout << "?? " << endl;
}
