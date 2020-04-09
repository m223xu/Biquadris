#include <vector>
#include <string>
#include "player.h"
#include "decorator.h"
#include "blind.h"

using namespace std;


Blind::Blind(Player* component, Xwindow* xw) : Decorator{ component }, xw{xw} {}
Blind::~Blind() {
}

int Blind::getPlayer(){
	return component->getPlayer();
}

void Blind::fixBlindCells(){
	if(xw){
		component->fixBlindCells();
	}
}

void Blind::levelup() {
	component->levelup();
}

void Blind::leveldown() {
	component->leveldown();
}

bool Blind::drop(bool & specialAction) {
	return component->drop(specialAction);
}

bool Blind::left(int i) {
	return component->left(i);
}

bool Blind::right(int i) {
	return component->right(i);
}

bool Blind::down(int i) {
	return component->down(i);
}

bool Blind::down() {
	return component->down();
}

bool Blind::clockwise(int i) {
	return component->clockwise(i);
}

bool Blind::counterclockwise(int i) {
	return component->counterclockwise(i);
}

vector<string> Blind::print() {
	vector<string> temp = component->print();
	for (int i = 9; i <= 17; ++i) {
		for (int j = 2; j <= 8; ++j) {
			temp[i][j] = '?';
		}
	}
	if(xw){
		int scale = component->getPlayer()==1 ? 0 : 312;
		xw->fillRectangle(56+scale, 280, 196,224,Xwindow::Grey);
	}
	return temp;
}



bool Blind::changeBlock(char c) {
	return component->changeBlock(c);
}

void Blind::random() {
	component->random();
}

void Blind::norandom(string file) {
	component->norandom(file);
}

void Blind::setNext() {
	component->setNext();
}

void Blind::restart(int level) {}

