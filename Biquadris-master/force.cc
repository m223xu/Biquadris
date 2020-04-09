#include <vector>
#include <string>
#include "player.h"
#include "decorator.h"
#include "force.h"

using namespace std;

Force::Force(Player* component) : Decorator{ component } {}

Force::~Force() {
}

int Force::getPlayer(){
	return component->getPlayer();
}

void Force::fixBlindCells(){
}

void Force::levelup() {
	component->levelup();
}

void Force::leveldown() {
	component->leveldown();
}

bool Force::drop(bool & specialAction) {
	return component->drop(specialAction);
}

bool Force::left(int i) {
	return component->left(i);
}

bool Force::right(int i) {
	return component->right(i);
}

bool Force::down(int i) {
	return component->down(i);
}

bool Force::down() {
	return component->down();
}

bool Force::clockwise(int i) {
	return component->clockwise(i);
}

bool Force::counterclockwise(int i) {
	return component->counterclockwise(i);
}

vector<string> Force::print() {
	return component->print();
}


bool Force::changeBlock(char c) {
	return component->changeBlock(c);
}

void Force::random() {
	component->random();
}

void Force::norandom(string file) {
	component->norandom(file);
}

void Force::setNext() {
	component->setNext();
}

void Force::restart(int level) {}

