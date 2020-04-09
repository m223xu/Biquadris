#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"
class Level4 : public Level{
  int seed;
  const int level = 4;
  bool isRandom = true;
  std::ifstream reader;
  char notRandomBlock();
public:
  Level4(int seed);
  int getLevel() override;
  char getNext() override;
  void norandom(std::string file) override;
  void random() override;
};
#endif

