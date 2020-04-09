#ifndef BLOCK_H
#define BLOCK_H
#include <vector>

class Cell;

// pure virtual class
class Block {
    protected:
        const int maxX = 10;
        const int maxY = 17;
    public:
        virtual ~Block();
        virtual int getLevel() = 0;
        virtual char getVal() = 0;
        virtual void removeCell(Cell *removedCell) = 0;
        virtual bool isCleared() = 0;
        bool inBounds (int x, int y);
        void orientationBounds(int &orientation);
        virtual void clockwise() = 0;
        virtual void counterClockwise() = 0;
        virtual void left() = 0;
        virtual void right() = 0;
        virtual bool down() = 0; // return false if down wasn't possible and true otherwise
};

#endif

