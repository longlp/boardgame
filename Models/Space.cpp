#include "Space.h"

Space::Space() {
	name = "";
	price = 0;
	owner = "No One ";
	up = false;
}

Space::Space(string name, int price) {
	this->name = name;
	this->price = price;
	owner = "No One ";
	up = false;
}

void Space::setName(string name) {
	this->name = name;
}
string Space::getName() {
	return name;
}

void Space::setOwner(string name) {
	owner = name;
}
int Space::getPrice() {
	return price;
}
bool Space::isChance() {
	return name.compare("Chance ") == 0;
}
bool Space::isChest() {
	return name.compare("Chest  ") == 0;
}
bool Space::isPrison() {
	return name.compare("Prison ") == 0;
}
bool Space::is2XSpeed() {
	return name.compare("2XSpeed") == 0;
}
bool Space::isPark() {
	return (name.compare("Park   ") == 0 || name.compare("Start  ") == 0)
			|| is2XSpeed();
}
bool Space::isFree() {
	return owner.compare("No One ") == 0 && !is2XSpeed();
}
string Space::getOwner() {
	return owner;
}
bool Space::isUp() {
	return up;
}
void Space::upgrade() {
	price *= 2;
	up = true;
}
