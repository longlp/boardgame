#include <string>
using namespace std;

#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
public:
	/**
	 * constructor
	 */
	Player();
	/**
	 * constructor
	 * @param pos space position of player, at start (0) initially for all players
	 * @param piece color piece of player
	 */
	Player(int pos, string piece);
	/**
	 * setter method for position
	 * @param pos space position of player, at start (0) initially for all players
	 */
	void setPos(int pos);
	/**
	 * setter method for piece
	 * @param piece color piece of player
	 */
	void setPiece(string piece);
	/**
	 * getter method for position
	 * @return position
	 */
	int getPos();
	/**
	 * getter method for piece
	 * @return piece
	 */
	string getPiece();
	/**
	 * method to roll 2 dices,
	 * change position of player
	 * by adding values of dices to position
	 * player loop in in circular spaces
	 * @return value of the 2 dices
	 */
	int rollDice(bool is2X);
	void setMoney(double money);
	double getMoney();
	void setLostTurn(int lostTurn);
	int getLostTurn();
private:
	int pos; //player space position
	string piece; //piece type
	double money;
	int lostTurn;
};

#endif /* PLAYER_H_ */
