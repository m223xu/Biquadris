#include "level2.h"
using namespace std;

Level2::Level2(int seed):seed{seed}{srand(seed);}

int Level2::getLevel(){return level;}

char Level2::getNext(){
  int r = rand() %7 + 1;
  if(r == 1){
    return 'I';
  }
  if(r == 2){
    return 'J';
  }
  if(r == 3){
    return 'L';
  }
  if(r == 4){
    return 'T';
  }
  if(r == 5){
    return 'O';
  }
  if(r == 6){
    return 'S';
  }
  return 'Z';
}

void Level2::norandom(string file){};
void Level2::random(){};

