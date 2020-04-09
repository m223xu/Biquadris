#include <vector>
#include <string>
#include "player.h"
#include "decorator.h"
#include "heavy.h"

using namespace std;

Heavy::Heavy(Player* component) : Decorator(component) {}

Heavy::~Heavy() {}

int Heavy::getPlayer(){
	return component->getPlayer();
}

void Heavy::fixBlindCells(){
}

void Heavy::levelup() {
	component->levelup();
}

void Heavy::leveldown() {
	component->leveldown();
}

bool Heavy::drop(bool & specialAction) {
	return component->drop(specialAction);
}

bool Heavy::left(int i) {
	if (component->left(i) == false) {
		return false;
	}
	if (component->down() == false) {
		return false;
	}
	if (component->down() == false) {
		return false;
	}
	return true;
}

bool Heavy::right(int i) {
	if (component->right(i) == false) {
		return false;
	}
	if (component->down() == false) {
		return false;
	}
	if (component->down() == false) {
		return false;
	}
	return true;
}

bool Heavy::down(int i) {
	if (component->down(i) == false) {
		return false;
	}
	if (component->down() == false) {
		return false;
	}
	if (component->down() == false) {
		return false;
	}
	return true;
}

bool Heavy::down() {
	return component->down();
}

bool Heavy::clockwise(int i) {
	return component->clockwise(i);
}

bool Heavy::counterclockwise(int i) {
	return component->counterclockwise(i);
}

vector<string> Heavy::print() {
	return component->print();
}


bool Heavy::changeBlock(char c) {
	return component->changeBlock(c);
}

void Heavy::random() {
	component->random();
}

void Heavy::norandom(string file) {
	component->norandom(file);
}

void Heavy::restart(int level) {}

void Heavy::setNext() {
	component->setNext();
}

