#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Player {
protected:
	Player();
public:
	virtual ~Player();
	virtual void levelup() = 0;
	virtual void leveldown() = 0;
	virtual bool drop(bool & specialAction) = 0; // returns false if game is end.
	virtual bool left(int i) = 0; // false means need to call drop, true means nothing will happen.
	virtual bool right(int i) = 0;
	virtual bool down(int i) = 0;
	virtual bool down() = 0;
	virtual bool clockwise(int i) = 0;
	virtual bool counterclockwise(int i) = 0;
	virtual std::vector<std::string> print() = 0;
	virtual bool changeBlock(char c) = 0;
	virtual void random() = 0;
	virtual void norandom(std::string file) = 0;
	virtual void restart(int level) = 0;
	virtual void setNext() = 0;
	virtual int getPlayer() = 0;
	virtual void fixBlindCells() = 0;
};

#endif

