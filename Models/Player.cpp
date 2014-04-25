#include "Player.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

Player::Player() {
	pos = 0;
	piece = "";
	money = 1200;
	lostTurn = 0;
}

Player::Player(int pos, string piece) {
	srand(time(NULL));
	this->pos = pos;
	this->piece = piece;
	money = 1200;
	lostTurn = 0;
}

void Player::setPos(int pos) {
	this->pos = pos;
}
void Player::setPiece(string piece) {
	this->piece = piece;
}
int Player::getPos() {
	return pos;
}
string Player::getPiece() {
	return piece;
}
int Player::rollDice(bool is2X) {
	int dice1 = rand() % 6 + 1;
//	int dice2 = rand() % 6 + 1;
	if (is2X) {
		cout << "2XSpeed, hurry up!!!!\n";
		pos = (pos + (dice1 * 2)) % 40;
	} else
		pos = (pos + (dice1)) % 40;
	return dice1;
}

void Player::setMoney(double money) {
	this->money = money;
}
double Player::getMoney() {
	return money;
}
void Player::setLostTurn(int lostTurn) {
	this->lostTurn = lostTurn;
}
int Player::getLostTurn() {
	return lostTurn;
}
