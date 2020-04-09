#include "level1.h"
using namespace std;

Level1::Level1(int seed):seed{seed}{srand(seed);}

int Level1::getLevel(){return level;}

char Level1::getNext(){
  int r = rand() %12 + 1;
  if(r == 1 || r == 2){
    return 'I';
  }
  if(r == 3 || r == 4){
    return 'J';
  }
  if(r == 5 || r == 6){
    return 'L';
  }
  if(r == 7 || r == 8){
    return 'T';
  }
  if(r == 9 || r == 10){
    return 'O';
  }
  if(r == 11){
    return 'S';
  }
  return 'Z';
}

void Level1::norandom(string file){};
void Level1::random(){};

