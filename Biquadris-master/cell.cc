#include "cell.h"

using namespace std;

// Cell constructor
Cell::Cell(int x, int y, Xwindow* xw, int player) :
x{x},
y{y},
xw{xw}{
  active = false;
  blockVal = ' ';
  width = player == 1 ? 0 : 312;
}

// Cell destructor
Cell::~Cell() {
  int height = y>=18 ? 4 : 0;
  if(xw){
    xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::White);
  }
}

// draws the cell a certain colour based on blockVal
void Cell::drawCell(){
  int height = y>=18 ? 4 : 0;
  switch(blockVal){
    case 'I' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::Red);
    break;
    case 'J' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::Yellow);
    break;
    case 'L' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::Blue);
    break;
    case 'Z' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::Purple);
    break;
    case 'S' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::DarkGreen);
    break;
    case 'T' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::Cyan);
    break;
    case 'O' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::Orange);
    break;
    case '?' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::Grey);
    break;
    case '*' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::Brown);
    break;
    case ' ' : xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::White);
    break;
  }
}

// draws in white over the cell
// void Cell::undrawCell() {
//   int height = y>=18 ? 4 : 0;
//   xw->fillRectangle(x*28+width, y*28+height+84, 28, 28,Xwindow::White);
// }

// returns x to caller
int Cell::getX() {
  return x;
}

// returns y to caller
int Cell::getY() {
  return y;
}

// returns blockVal
char Cell::getVal() {
  return blockVal;
}

// returns active to the caller
bool Cell::isActive() {
  return active;
}

// sets the Cell to be active and updates blockval
void Cell::setActive(char newBlockVal) {
  active = true;
  blockVal = newBlockVal;
  if(xw){
    drawCell();
  }
}

// sets the cell to non-active and sets blockval to ' '
void Cell::deActive() {
  active = false;
  blockVal = ' ';
  if(xw){
    drawCell();
  }
}

// updates x and y when rows are cleared from the board
void Cell::setCoords(int newX, int newY) {
  x = newX;
  y = newY;
  if(xw){
    drawCell();
  }
}

