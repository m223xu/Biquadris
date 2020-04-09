#include <cstdlib>
#include <iostream>
#include "sblock.h"

using namespace std;

bool sBlock::cellAvailable (int newX, int newY) {
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

sBlock::sBlock(int level, Cell *bottomLeft,
            std::vector<std::vector<Cell *>> *board) :
    level{level},
    bottomLeft{bottomLeft},
    board{board} {
    orientation = 0;
    blockVal = 'S';
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    block.push_back((*board)[bottomLeftY][bottomLeftX]);
    block.push_back((*board)[bottomLeftY][bottomLeftX + 1]);
    block.push_back((*board)[bottomLeftY - 1][bottomLeftX + 1]);
    block.push_back((*board)[bottomLeftY - 1][bottomLeftX + 2]);
    for (int i = 0; i < 4; ++i) {
        block[i]->setActive(blockVal);
    }
}

sBlock::~sBlock() {
    int blockSize = static_cast<int>(block.size());
    for (int i = 0; i < blockSize; ++i) {
        block[i]->deActive();
    }
}

int sBlock::getLevel() {
    return level;
}

char sBlock::getVal() {
    return blockVal;
}

// removes cell from block vector if in the vector
void sBlock::removeCell(Cell *removedCell) {
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
bool sBlock::isCleared() {
    if (block.size() == 0) {
        return true;
    }
    return false;
}

// could make a rotation(orientation) function
void sBlock::clockwise() {
    // rotating the block clockwise
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    if (orientation == 0  || orientation == 2) {
        // checking if we can rotate
        if (cellAvailable(bottomLeftX, bottomLeftY - 1) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX, bottomLeftY - 2) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 1, bottomLeftY) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 1, bottomLeftY - 1) == false) {
            return;
        }

        // updating block's cells to new cells
        for (int i = 0; i < 4; ++i) {
            block[i]->deActive();
        }
        block[0] = (*board)[bottomLeftY - 1][bottomLeftX];
        block[1] = (*board)[bottomLeftY - 2][bottomLeftX];
        block[2] = (*board)[bottomLeftY][bottomLeftX + 1];
        block[3] = (*board)[bottomLeftY - 1][bottomLeftX + 1];
        for (int i = 0; i < 4; ++i) {
            block[i]->setActive(blockVal);
        }
    }
    else if (orientation == 1  || orientation == 3) {
        // checking if we can rotate
        if (cellAvailable(bottomLeftX, bottomLeftY) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 1, bottomLeftY) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 1, bottomLeftY - 1) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 2, bottomLeftY - 1) == false) {
            return;
        }

        // updating block's cells to new cells
        for (int i = 0; i < 4; ++i) {
            block[i]->deActive();
        }
        block[0] = (*board)[bottomLeftY][bottomLeftX];
        block[1] = (*board)[bottomLeftY][bottomLeftX + 1];
        block[2] = (*board)[bottomLeftY - 1][bottomLeftX + 1];
        block[3] = (*board)[bottomLeftY - 1][bottomLeftX + 2];
        for (int i = 0; i < 4; ++i) {
            block[i]->setActive(blockVal);
        }
    }
    orientationBounds(++orientation);
}

// could make a rotation(orientation) function
void sBlock::counterClockwise() {
    // rotating the block counterclockwise
    int bottomLeftX = bottomLeft->getX();
    int bottomLeftY = bottomLeft->getY();
    if (orientation == 0 || orientation == 2) {
        // checking if we can rotate
        if (cellAvailable(bottomLeftX, bottomLeftY - 1) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX, bottomLeftY - 2) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 1, bottomLeftY) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 1, bottomLeftY - 1) == false) {
            return;
        }

        // updating block's cells to new cells
        for (int i = 0; i < 4; ++i) {
            block[i]->deActive();
        }
        block[0] = (*board)[bottomLeftY - 1][bottomLeftX];
        block[1] = (*board)[bottomLeftY - 2][bottomLeftX];
        block[2] = (*board)[bottomLeftY][bottomLeftX + 1];
        block[3] = (*board)[bottomLeftY - 1][bottomLeftX + 1];
        for (int i = 0; i < 4; ++i) {
            block[i]->setActive(blockVal);
        }
    }
    else if (orientation == 1 || orientation == 3) {
        // checking if we can rotate
        if (cellAvailable(bottomLeftX, bottomLeftY) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 1, bottomLeftY) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 1, bottomLeftY - 1) == false) {
            return;
        }
        if (cellAvailable(bottomLeftX + 2, bottomLeftY - 1) == false) {
            return;
        }

        // updating block's cells to new cells
        for (int i = 0; i < 4; ++i) {
            block[i]->deActive();
        }
        block[0] = (*board)[bottomLeftY][bottomLeftX];
        block[1] = (*board)[bottomLeftY][bottomLeftX + 1];
        block[2] = (*board)[bottomLeftY - 1][bottomLeftX + 1];
        block[3] = (*board)[bottomLeftY - 1][bottomLeftX + 2];
        for (int i = 0; i < 4; ++i) {
            block[i]->setActive(blockVal);
        }
    }
    orientationBounds(--orientation);
}


void sBlock::left() {
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

void sBlock::right() {
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
bool sBlock::down() {
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

