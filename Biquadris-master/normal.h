#ifndef __NORMAL_H__
#define __NORMAL_H__

#include <string>
#include <vector>
#include "player.h"
#include "block.h"
#include "cell.h"
#include "level.h"
#include "window.h"

class Normal : public Player {
	int seed;
	std::string file0;
	Level* level;
	int score;
	int highscore;
	int failedMoves;
	Block* cur;
	Block* next;
	Xwindow* xw;
	int playerNum;
	std::vector<std::vector<Cell*>> board;  // 11*22
	std::vector<Block*> blocks; // All active blocks.

	// helper
	Block* createBlock(char c, Cell* bl);
	bool dropStar(); // return true if dropstar successfully, return false means game should be end.
public:
	Normal(int l, std::string file0, int seed, Xwindow* xw, int playerNum);
	~Normal();
	void levelup() override;
	void leveldown() override;
	bool drop(bool & specialAction) override;
	bool left(int i) override;
	bool right(int i) override;
	bool down(int i) override;
	bool down() override;
	bool clockwise(int i) override;
	bool counterclockwise(int i) override;
	std::vector<std::string> print() override;
	bool changeBlock(char c) override;
	void random() override;
	void norandom(std::string file) override;
	void restart(int level) override;
	void setNext() override;
	int getPlayer() override;
	void fixBlindCells() override;
};

#endif

