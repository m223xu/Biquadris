#include <cstdlib>
#include <iostream>
#include "oblock.h"

using namespace std;

bool oBlock::cellAvailable (int newX, int newY) {
    if (inBounds(newX, newY)) {
        if ((*board)[newY][newX]->isActive()) {
            for (int i = 0; i < 4; ++i) {
                if (block[i] == (*board)[newY][newX]) {
                    return true;
                }
            }
        }
        else {
            return true;
        }
    }
    return false;
}

oBlock::oBlock(int level, Cell *bottomLeft,
            std::vector<std::vector<Cell *>> *board) :
    level{level},
    bottomLeft{bottomLeft},
    board{board} {
    blockVal = 'O';
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    block.push_back((*board)[bottomLeftY][bottomLeftX]);
    block.push_back((*board)[bottomLeftY][bottomLeftX + 1]);
    block.push_back((*board)[bottomLeftY - 1][bottomLeftX + 1]);
    block.push_back((*board)[bottomLeftY - 1][bottomLeftX]);
    for (int i = 0; i < 4; ++i) {
        block[i]->setActive(blockVal);
    }
}

oBlock::~oBlock() {
    int blockSize = static_cast<int>(block.size());
    for (int i = 0; i < blockSize; ++i) {
        block[i]->deActive();
    }
}

int oBlock::getLevel() {
    return level;
}

char oBlock::getVal() {
    return blockVal;
}

// removes cell from block vector if in the vector
void oBlock::removeCell(Cell *removedCell) {
    int blockSize = block.size();
    for (int i = 0; i < blockSize; ++i) {
        if (block[i] == removedCell) {
            block.erase(block.begin() + i);
            return;
        }
    }
}

// returns true if the block is not on the board anymore
//   and false otherwise
bool oBlock::isCleared() {
    if (block.size() == 0) {
        return true;
    }
    return false;
}

// oBlock rotation does nothing
void oBlock::clockwise() {
}

// oBlock rotation does nothing
void oBlock::counterClockwise() {
}


void oBlock::left() {
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    int newX;
    int newY;
    
    for (int i = 0; i < 4; ++i) {
        newX = block[i]->getX() - 1;
        newY = block[i]->getY();
        if (cellAvailable(newX, newY) == false) {
            return;
        }
    }
    
    for (int i = 0; i < 4; ++i) {
        block[i]->deActive();
    }
    for (int i = 0; i < 4; ++i) {
        newX = block[i]->getX() - 1;
        newY = block[i]->getY();
        block[i] = (*board)[newY][newX];
    }
    for (int i = 0; i < 4; ++i) {
        block[i]->setActive(blockVal);
    }
    bottomLeft = (*board)[bottomLeftY][bottomLeftX - 1];
}

void oBlock::right() {
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    int newX;
    int newY;
    
    for (int i = 0; i < 4; ++i) {
        newX = block[i]->getX() + 1;
        newY = block[i]->getY();
        if (cellAvailable(newX, newY) == false) {
            return;
        }
    }

    for (int i = 0; i < 4; ++i) {
        block[i]->deActive();
    }
    for (int i = 0; i < 4; ++i) {
        newX = block[i]->getX() + 1;
        newY = block[i]->getY();
        block[i] = (*board)[newY][newX];
    }
    for (int i = 0; i < 4; ++i) {
        block[i]->setActive(blockVal);
    }
    bottomLeft = (*board)[bottomLeftY][bottomLeftX + 1];
}

// return false if down wasn't possible and true otherwise
bool oBlock::down() {
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    int newX;
    int newY;

    for (int i = 0; i < 4; ++i) {
        newX = block[i]->getX();
        newY = block[i]->getY() + 1;
        if (cellAvailable(newX, newY) == false) {
            return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        block[i]->deActive();
    }
    for (int i = 0; i < 4; ++i) {
        newX = block[i]->getX();
        newY = block[i]->getY() + 1;
        block[i] = (*board)[newY][newX];
    }
    for (int i = 0; i < 4; ++i) {
        block[i]->setActive(blockVal);
    }
    bottomLeft = (*board)[bottomLeftY + 1][bottomLeftX];
    return true;
}

