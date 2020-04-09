#include <cstdlib>
#include <iostream>
#include "iblock.h"

using namespace std;

bool iBlock::cellAvailable (int newX, int newY) {
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

iBlock::iBlock(int level, Cell *bottomLeft,
            std::vector<std::vector<Cell *>> *board) :
    level{level},
    bottomLeft{bottomLeft},
    board{board} {
    orientation = 0;
    blockVal = 'I';
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    // could put into a for loop (didn't for continuity)
    block.push_back((*board)[bottomLeftY][bottomLeftX]);
    block.push_back((*board)[bottomLeftY][bottomLeftX + 1]);
    block.push_back((*board)[bottomLeftY][bottomLeftX + 2]);
    block.push_back((*board)[bottomLeftY][bottomLeftX + 3]);
    for (int i = 0; i < 4; ++i) {
        block[i]->setActive(blockVal);
    }
}

iBlock::~iBlock() {
    int blockSize = static_cast<int>(block.size());
    for (int i = 0; i < blockSize; ++i) {
        block[i]->deActive();
    }
}

int iBlock::getLevel() {
    return level;
}

char iBlock::getVal() {
    return blockVal;
}

// removes cell from block vector if in the vector
void iBlock::removeCell(Cell *removedCell) {
    int blockSize = static_cast<int>(block.size());
    for (int i = 0; i < blockSize; ++i) {
        if (block[i] == removedCell) {
            block.erase(block.begin() + i);
            return;
        }
    }
}

// returns true if the block is not on the board anymore
//   and false otherwise
bool iBlock::isCleared() {
    if (block.size() == 0) {
        return true;
    }
    return false;
}

// could make a rotation(orientation) function
void iBlock::clockwise() {
    // rotating the block clockwise
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    if (orientation == 0 || orientation == 2) {
        for (int i = 1; i < 4; ++i) {
            if (cellAvailable(bottomLeftX, bottomLeftY - i) == false) {
                return;
            }
        }
        for (int i = 0; i < 4; ++i) {
            block[i]->deActive();
            block[i] = (*board)[bottomLeftY - i][bottomLeftX];
            block[i]->setActive(blockVal);
        }
    }
    else if (orientation == 1 || orientation == 3) {
        for (int i = 1; i < 4; ++i) {
            if (cellAvailable(bottomLeftX + i, bottomLeftY) == false) {
                return;
            }
        }
        for (int i = 0; i < 4; ++i) {
            block[i]->deActive();
            block[i] = (*board)[bottomLeftY][bottomLeftX + i];
            block[i]->setActive(blockVal);
        }
    }
    orientationBounds(++orientation);
}

// could make a rotation(orientation) function
void iBlock::counterClockwise() {
    // rotating the block counter clockwise
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    if (orientation == 0  || orientation == 2) {
        for (int i = 1; i < 4; ++i) {
            if (cellAvailable(bottomLeftX, bottomLeftY - i) == false) {
                return;
            }
        }
        for (int i = 0; i < 4; ++i) {
            block[i]->deActive();
            block[i] = (*board)[bottomLeftY - i][bottomLeftX];
            block[i]->setActive(blockVal);
        }
    }
    else if (orientation == 1 || orientation == 3) {
        for (int i = 1; i < 4; ++i) {
            if (cellAvailable(bottomLeftX + i, bottomLeftY) == false) {
                return;
            }
        }
        for (int i = 0; i < 4; ++i) {
            block[i]->deActive();
            block[i] = (*board)[bottomLeftY][bottomLeftX + i];
            block[i]->setActive(blockVal);
        }
    }
    orientationBounds(--orientation);
}


void iBlock::left() {
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

void iBlock::right() {
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
bool iBlock::down() {
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

