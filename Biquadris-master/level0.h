#ifndef LEVEL0_H
#define LEVEL0_H
#include "level.h"
class Level0 : public Level{
  const int level = 0;
  std::string fileName;
  std::ifstream reader;
public:
  Level0(std::string fileName);
  int getLevel() override;
  char getNext() override;
  void norandom(std::string file) override;
  void random() override;
  ~Level0();
};
#endif

