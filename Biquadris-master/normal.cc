#include <string>
#include <iostream>
#include <vector>
#include "normal.h"
#include "player.h"
#include "block.h"
#include "cell.h"
#include "level.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "zblock.h"
#include "sblock.h"
#include "oblock.h"
#include "tblock.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"

using namespace std;


bool Normal::drop(bool & specialAction) {
	// go down.
	bool downwards = true;
	do {
		downwards = cur->down();
	} while (downwards);
	cur = nullptr;
	// check each row (score,special action) and remove cleared cells from board and active blocks, then move rows downwards and reset the cell coords
	int cleared_rows = 0;
	for (int i = 17; i >= 0; --i) {
		bool row_iscleared = true;
		for (int j = 0; j < 11; ++j) {
			// Reset the coords.
			board[i][j]->setCoords(j, i + cleared_rows);
			if (board[i][j]->isActive() == false) {
				row_iscleared = false;
			}
		}
		if (!row_iscleared) {
			continue;
		}
		// The i's row is cleared.
		cleared_rows += 1;
		// Now, we will remove this row of cells from blocks.
		for (int j = 0; j < 11; ++j) {
			for (int k = 0; k < static_cast<int>(blocks.size()); ++k) {
				blocks[k]->removeCell(board[i][j]);
			}
		}
		// Now, we will remove this row from board.
		for (int j = 0; j < 11; ++j) {
			delete board[i][j];
			board[i][j] = nullptr;
		}
		board.erase(board.begin() + i);
	}
	// fill in the board to size 11*22.
	for (int i = cleared_rows - 1; i >= 0; --i) {
		vector<Cell*> row(11, nullptr);
		for (int j = 0; j < 11; ++j) {
			row[j] = new Cell{ j,i,xw,playerNum};
		}
		board.insert(board.begin(), row);
	}
	// SpecialAction?
	if (cleared_rows >= 2) {
		specialAction = true;
	}
	// Score calculation.
	int ln = level->getLevel();
	if (cleared_rows > 0) {
		score += (cleared_rows + ln) * (cleared_rows + ln);
	}
	if (highscore < score) {
		highscore = score;
	}
	// check each active blocks by isCleared(), if a block is cleared, remove it by delete block and calc score.
	for (int i = 0; i < static_cast<int>(blocks.size()); ++i) {
		if (blocks[i]->isCleared()) {
			int blockLevel = blocks[i]->getLevel();
			score += (blockLevel + 1) * (blockLevel + 1);
			delete blocks[i];
			blocks.erase(blocks.begin() + i);
			--i;
		}
	}
	if (highscore < score) {
		highscore = score;
	}
	// failedmoves++ if no row is cleared, and if level 4 and failedmoves % 5 == 0, dropstar(), if dropstar is false return false.
	if (cleared_rows == 0) {
		++failedMoves;
	}
	else {
		failedMoves = 0;
	}
	if (ln == 4 and failedMoves > 0 and failedMoves % 5 == 0) {
		bool ds = dropStar();
		if (ds == false) {
			return false;
		}
	}

	// put the next block on the board, c = next->getVal(), delete next and create a new block for cur, if changeBlock(c) is false return false
	char c = next->getVal();
	delete next;
	next = nullptr;

	bool cb = changeBlock(c);
	if (cb == false) {
		return false;
	}
	return true;
}


Normal::Normal(int l, string file0, int seed, Xwindow* xw, int playerNum) : seed(seed), file0(file0), level(nullptr), score(0), highscore(0),
failedMoves(0), cur(nullptr), next(nullptr), xw(xw), playerNum(playerNum) {
	if (l == 0) {
		level = new Level0{ file0 };
	}
	else if (l == 1) {
		level = new Level1{ seed };
	}
	else if (l == 2) {
		level = new Level2{ seed };
	}
	else if (l == 3) {
		level = new Level3{ seed };
	}
	else {
		level = new Level4{ seed };
	}
	for (int i = 0; i < 22; ++i) {
		vector<Cell*> row;
		for (int j = 0; j < 11; ++j) {
			Cell* c = new Cell{ j,i,xw,playerNum };
			row.emplace_back(c);
		}
		board.emplace_back(row);
	}
	cur = createBlock(this->level->getNext(), board[3][0]);
	blocks.emplace_back(cur);
}

Normal::~Normal() {
	delete level;
	delete next;
	for (auto & p : blocks) {
		delete p;
	}
	for (auto & row : board) {
		for (auto & p : row) {
			delete p;
		}
	}
}



bool Normal::changeBlock(char c) {
	if (cur != nullptr) {
		delete cur;
		cur = nullptr;
		blocks.pop_back();
	}
	int l = level->getLevel();
	Cell* bl = board[3][0];
	if (c == 'I') {
		if (board[3][0]->isActive() or board[3][1]->isActive() or board[3][2]->isActive() or board[3][3]->isActive()) {
			return false;
		}
		cur = new iBlock{ l,bl,&board };
	}
	if (c == 'L') {
		if (board[3][0]->isActive() or board[3][1]->isActive() or board[3][2]->isActive()) {
			return false;
		}
		cur = new lBlock{ l,bl,&board };
	}
	if (c == 'J') {
		if (board[3][0]->isActive() or board[3][1]->isActive() or board[3][2]->isActive()) {
			return false;
		}
		cur = new jBlock{ l,bl,&board };
	}
	if (c == 'Z') {
		if (board[3][1]->isActive() or board[3][2]->isActive()) {
			return false;
		}
		cur = new zBlock{ l,bl,&board };
	}
	if (c == 'S') {
		if (board[3][0]->isActive() or board[3][1]->isActive()) {
			return false;
		}
		cur = new sBlock{ l,bl,&board };
	}
	if (c == 'O') {
		if (board[3][0]->isActive() or board[3][1]->isActive()) {
			return false;
		}
		cur = new oBlock{ l,bl,&board };
	}
	if (c == 'T') {
		if (board[3][1]->isActive()) {
			return false;
		}
		cur = new tBlock{ l,bl,&board };
	}
	blocks.emplace_back(cur);
	return true;
}

void Normal::setNext() {
	char c = level->getNext();
	next = createBlock(c, board[19][0]);
}


Block* Normal::createBlock(char c, Cell* bl) {
	int l = level->getLevel();
	if (c == 'I') {
		return new iBlock{ l,bl,&board };
	}
	if (c == 'L') {
		return new lBlock{ l,bl,&board };
	}
	if (c == 'J') {
		return new jBlock{ l,bl,&board };
	}
	if (c == 'Z') {
		return new zBlock{ l,bl,&board };
	}
	if (c == 'S') {
		return new sBlock{ l,bl,&board };
	}
	if (c == 'O') {
		return new oBlock{ l,bl,&board };
	}
	if (c == 'T') {
		return new tBlock{ l,bl,&board };
	}
	return nullptr;
}

bool Normal::dropStar() {
	if (board[0][5]->isActive()) {
		return false;
	}
	int i = 1;
	while (i < 18) {
		if (board[i][5]->isActive()) {
			board[i - 1][5]->setActive('*');
			break;
		}
		++i;
	}
	if (i == 18) {
		board[17][5]->setActive('*');
	}
	return true;
}

void Normal::levelup() {
	int i = level->getLevel();
	if (i == 0) {
		delete level;
		level = new Level1{ seed };
	}
	else if (i == 1) {
		delete level;
		level = new Level2{ seed };
	}
	else if (i == 2) {
		delete level;
		level = new Level3{ seed };
	}
	else if (i == 3) {
		delete level;
		level = new Level4{ seed };
	}
}

void Normal::leveldown() {
	int i = level->getLevel();
	if (i == 4) {
		delete level;
		level = new Level3{ seed };
	}
	else if (i == 3) {
		delete level;
		level = new Level2{ seed };
	}
	else if (i == 2) {
		delete level;
		level = new Level1{ seed };
	}
	else if (i == 1) {
		delete level;
		level = new Level0{ file0 };
	}
}

bool Normal::left(int i) {
	while (i > 0) {
		cur->left();
		--i;
	}
	if (level->getLevel() == 3 or level->getLevel() == 4) {
		if (cur->down()) {
			return true;
		}
		else {
			return false;
		}
	}
	return true;
}

bool Normal::right(int i) {
	while (i > 0) {
		cur->right();
		--i;
	}
	if (level->getLevel() == 3 or level->getLevel() == 4) {
		if (cur->down()) {
			return true;
		}
		else {

			return false;
		}
	}
	return true;
}

bool Normal::down(int i) {
	while (i > 0) {
		cur->down();
		--i;
	}
	if (level->getLevel() == 3 or level->getLevel() == 4) {
		if (cur->down()) {
			return true;
		}
		else {
			return false;
		}
	}
	return true;
}

bool Normal::down() {
	return cur->down();
}

bool Normal::clockwise(int i) {
	while (i > 0) {
		cur->clockwise();
		--i;
	}
	if (level->getLevel() == 3 or level->getLevel() == 4) {
		if (cur->down()) {
			return true;
		}
		else {
			return false;
		}
	}
	return true;
}

bool Normal::counterclockwise(int i) {
	while (i > 0) {
		cur->counterClockwise();
		--i;
	}
	if (level->getLevel() == 3 or level->getLevel() == 4) {
		if (cur->down()) {
			return true;
		}
		else {
			return false;
		}
	}
	return true;
}



vector<string> Normal::print() {
	int scale = playerNum==1 ? 0 : 312;

	vector<string> retval = {};
	string playerRow = "Player " + to_string(playerNum);
	string levelRow = "Level:    ";
	int l = level->getLevel();
	levelRow = levelRow + to_string(l);
	retval.emplace_back(levelRow);
	string scoreRow = "Score:";
	string s = to_string(score);
	int i = 5;
	while (i > static_cast<int>(s.length())) {
		scoreRow = scoreRow + " ";
		--i;
	}
	scoreRow = scoreRow + s;
	if(xw){
		xw->fillRectangle(scale+3,0,308,81,Xwindow::White);
		xw->drawString(scale+3,20,playerRow);
		xw->drawString(scale+3,40,levelRow);
		xw->drawString(scale+3,60,scoreRow);
	}
	retval.emplace_back(scoreRow);

	retval.emplace_back("-----------");
	string row;
	for (int i = 0; i < 18; ++i) {
		row = "";
		for (int j = 0; j < 11; ++j) {
			if (board[i][j]->isActive()) {
				row = row + board[i][j]->getVal();
			}
			else {
				row = row + " ";
			}
		}
		retval.emplace_back(row);
	}

	retval.emplace_back("-----------");

	retval.emplace_back("Next:      ");

	for (int i = 18; i < 22; ++i) {
		row = "";
		for (int j = 0; j < 11; ++j) {
			if (board[i][j]->isActive()) {
				row = row + board[i][j]->getVal();
			}
			else {
				row = row + " ";
			}
		}
		retval.emplace_back(row);
	}

	return retval;
}

void Normal::restart(int level) {
	score = 0;
	failedMoves = 0;
	for (int i = 0; i < 22; ++i) {
		for (int j = 0; j < 11; ++j) {
			board[i][j]->deActive();
		}
	}
	for (Block* p : blocks) {
		delete p;
	}
	while (blocks.size() > 0) {
		blocks.pop_back();
	}
	cur = nullptr;
	delete next;
	next = nullptr;
	delete this->level;
	if (level == 0) {
		this->level = new Level0{ file0 };
	}
	else if (level == 1) {
		this->level = new Level1{ seed };
	}
	else if (level == 2) {
		this->level = new Level2{ seed };
	}
	else if (level == 3) {
		this->level = new Level3{ seed };
	}
	else {
		this->level = new Level4{ seed };
	}
	if(xw){
		int scale = playerNum==1 ? 0 : 312;
		xw->fillRectangle(scale,84,308,504,Xwindow::White);
	}
	cur = createBlock(this->level->getNext(), board[3][0]);
	blocks.emplace_back(cur);
}

void Normal::random() {
	level->random();
}

void Normal::norandom(string file) {
	level->norandom(file);
}

int Normal::getPlayer(){
	return playerNum;
}

void Normal::fixBlindCells(){
	for(int i = 3; i < 12; i++){
		for(int j = 2; j < 10; j++){
			board[i][j]->drawCell();
		}
	}
}

