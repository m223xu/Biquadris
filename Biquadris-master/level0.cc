#include "level0.h"
using namespace std;

Level0::Level0(string fileName):fileName{fileName}{reader.open(fileName);}

int Level0::getLevel(){return level;}

char Level0::getNext(){
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
  return this->getNext();
}
void Level0::norandom(string file){};
void Level0::random(){};

Level0::~Level0(){
  reader.close();
}

