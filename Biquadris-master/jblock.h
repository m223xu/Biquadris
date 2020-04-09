#ifndef JBLOCK_H
#define JBLOCK_H

#include "cell.h"
#include "block.h"

class jBlock : public Block{
    // for rotation (0 = initPos, 1 = 1cw, 2 = 2cw, 3 = 3cw)
    //   4cw is just initPos
    int orientation;
    // for scoring
    int level;
    // for setting a new cell active in a block
    char blockVal;
    // for moving/rotation
    Cell *bottomLeft;
    // keep track of which cells are part of the block
    std::vector<Cell *> block;
    // keep track of which cells are active
    std::vector<std::vector<Cell *> > *board;

    // checks if a cell at newX and newY is available in board
    //   if it is in the board, is active, and is part of the current block
    //   it returns true. It returns false otherwise.
    bool cellAvailable(int newX, int newY);

    public:
    jBlock(int level, Cell *bottomLeft,
            std::vector<std::vector<Cell *>> *board);
    ~jBlock();
    int getLevel() override; // return the level it was created in
    char getVal() override; // return the blockVal
    void removeCell(Cell *removedCell) override; // remove the cell from the block
    bool isCleared() override; // return if the cell is cleared or not
    void clockwise() override; // rotate block clockwise if possible
    void counterClockwise() override; // rotate block cclockwise ...
    void left() override; // move block left ...
    void right() override; // move block right ...
    bool down() override; // move block down and return true (false if not possible)
};

#endif

