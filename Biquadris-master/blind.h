#ifndef __BLIND_H__
#define __BLIND_H__

#include "player.h"
#include "decorator.h"
#include <vector>
#include <string>
#include "window.h"

class Blind : public Decorator {
public:
	Xwindow* xw;
	Blind(Player* component, Xwindow* xw);
	~Blind();
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

