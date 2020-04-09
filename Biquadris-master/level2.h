#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"
class Level2 : public Level{
  int seed;
  const int level = 2;
public:
  Level2(int seed);
  int getLevel() override;
  char getNext() override;
  void norandom(std::string file) override;
  void random() override;
};
#endif

