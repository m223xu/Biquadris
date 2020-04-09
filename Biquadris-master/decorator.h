#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include "player.h"


class Decorator : public Player {
public:
	Player* component;
	~Decorator();
protected:
	Decorator(Player* component);

};

#endif

