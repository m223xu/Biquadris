#include "block.h"

using namespace std;

bool Block::inBounds (int x, int y) {
    if (x < 0 || x > maxX || y < 0 || y > maxY) {
        return false;
    }
    return true;
}

void Block::orientationBounds(int &orientation) {
    if (orientation < 0) {
        orientation = 3;
    }
    if (orientation > 3) {
        orientation = 0;
    }
}

Block::~Block() {
}

