#ifndef LEVEL_H
#define LEVEL_H

//#include "block.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>


class Level{
public:
  virtual int getLevel() = 0;
  virtual char getNext() = 0;
  virtual ~Level() = 0;
  virtual void norandom(std::string file) = 0;
  virtual void random() = 0;
};




#endif

