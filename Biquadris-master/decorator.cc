#include "player.h"
#include "decorator.h"

using namespace std;

Decorator::Decorator(Player* component) : component(component) {}
Decorator::~Decorator() {
  delete component;
}

