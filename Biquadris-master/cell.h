#ifndef CELL_H
#define CELL_H

#include "window.h"

class Cell {
    // Xwindow *cWindow;
    int x;
    int y;
    bool active;
    char blockVal;
    Xwindow* xw;
    int width;
    public:
    Cell(int x, int y, Xwindow* xw, int playerNum);
    ~Cell();
    void drawCell();
  //  void undrawCell();
    int getX();
    int getY();
    char getVal();
    bool isActive();
    void setActive(char newBlockVal);
    void deActive();
    void setCoords(int newX, int newY);

    // friend ostream &operator<<(ostream &out, Cell &cell) or something
};

#endif

