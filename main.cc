#include "grid.h"
#include "textdisplay.h"
#include "cell.h"
#include "window.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
   string s;
   string command;
   Grid *mygrid = NULL;
   int numSteps = 0;
   int change;
   int size;
   bool gameOn = false;
   while(getline(cin,s)) {
      stringstream ss(s);
      ss >> command;
      if((!gameOn) && (command == "new")) {
         ss >> size;
         //cout << "The size is -> " << size << endl;
         if(mygrid !=  NULL) {
            //cout << size << " creating\n" << endl;
            delete mygrid;
            mygrid = new Grid;
            mygrid->init(size);
         }
         if(mygrid == NULL) {
            mygrid = new Grid;
            mygrid->init(size);
         }
      }
      if(command == "init") {
         int r;
         int c;
         int state;
         while(getline(cin,s)) {
            stringstream tempss(s);
            tempss >> r >> c;
            if((r == -1) && (c == -1)) break;
            if ((r >= 0) && (r < size) && ( c >= 0) && (c < size)) { //valid coords
               tempss >> state;
               mygrid->init(r,c,state);
            }
         }
         cout << *mygrid;
         if((gameOn) && (mygrid->isWon() == true)) {
            cout << "Won" << endl;
            break;
         }
      }
      if(command == "include") {
         int fr;
         int fc;
         int fstate;
         string file;
         ss >> file;
         fstream filein(file.c_str());
         while(getline(filein, s)) {
            stringstream tempfile(s);
            tempfile >> fr >> fc;
            if((fr == -1) && (fc == -1)) break;
            if ((fr >= 0) && (fr < size) && (fc >= 0) && (fc < size)) { //valid coords
               tempfile >> fstate;
               mygrid->init(fr,fc,fstate);
            }
         }
         cout << *mygrid;
         if((gameOn) && (mygrid->isWon() == true)) {
            cout << "Won" << endl;
            break;
         }
      }
      if(command == "game") {
         gameOn = true;
         ss >> numSteps;
         if(numSteps != 1) {
            cout << numSteps << " moves left" << endl;
         }
         if(numSteps == 1) {
            cout << numSteps << " move left" << endl;
         }
         if(mygrid->isWon() == true) {
            cout << "Won" << endl;
            break;
         }
      }
      if(command == "switch") {
         numSteps--;
         ss >> change;
         mygrid->change(change);
         if(mygrid->isWon() == true) {
            cout << *mygrid;
            if(numSteps != 1) {
               cout << numSteps << " moves left" << endl;
            }
            if(numSteps == 1) {
               cout << numSteps << " move left" << endl;
            }
            cout << "Won" << endl;
            break;
         }
         if(numSteps > 1) {
            cout << *mygrid;
            cout << numSteps << " moves left" << endl;
         }
         if(numSteps == 1) {
            cout << *mygrid;
            cout << numSteps << " move left" << endl;
         }
         if((numSteps == 0) && (mygrid->isWon() == false)) {
            cout << *mygrid;
            cout << numSteps << " moves left" << endl;
            cout << "Lost" << endl;
            break;
         }
      }
   } // end of the while loop
   //free memory
   if(mygrid != NULL) {
      delete mygrid;
   }
}
