#ifndef LEVEL1_H
#define LEVEL1_H
#include "level.h"
class Level1 : public Level{
  int seed;
  const int level = 1;
public:
  Level1(int seed);
  int getLevel() override;
  char getNext() override;
  void norandom(std::string file) override;
  void random() override;
};
#endif

