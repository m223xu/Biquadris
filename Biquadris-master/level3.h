#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"
class Level3 : public Level{
  int seed;
  const int level = 3;
  bool isRandom = true;
  std::ifstream reader;
  char notRandomBlock();
public:
  Level3(int seed);
  int getLevel() override;
  char getNext() override;
  void norandom(std::string file) override;
  void random() override;
};
#endif

