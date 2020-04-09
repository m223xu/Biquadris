#include "level3.h"
using namespace std;

Level3::Level3(int seed):seed{seed}{srand(seed);}

int Level3::getLevel(){return level;}

char Level3::getNext(){
  if(!isRandom) return this->notRandomBlock();
  int r = rand() %9 + 1;
  if(r == 1){
    return'I';
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
  if(r == 6 || r == 7){
    return 'S';
  }
  return 'Z';
}

void Level3::norandom(string file){
  isRandom = false;
  reader.open(file);
}

void Level3::random(){
  reader.close();
  isRandom = true;
}

char Level3::notRandomBlock(){
  char var = 0;
  if(reader.eof()){
    reader.clear();
    reader.seekg(0,reader.beg);
    reader >> var;
  }
  else{
    reader >> var;
  }
  if(97 <= var && var <=122){
    return var-32;
  }
  else if(65 <= var && var <=90){
    return var;
  }
  if(var == 0) return 'I';
  return this->notRandomBlock();
}

