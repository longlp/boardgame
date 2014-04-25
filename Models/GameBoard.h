#include <vector>
#include <string>
#include "Space.h"
#include "Player.h"
using namespace std;

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

class Game_Board {
public:
	/**
	 * constructor
	 */
	Game_Board();
	/**
	 *game loop
	 *loop through player
	 *each player roll dice and move to his new position
	 */
	void start();
	void chest(int* i);
	void chance(int* i);
	void printBoard();
private:
	//players in the game
	vector<Player*> players;
	//spaces in the board
	vector<Space*> spaces;
	//available pieces for players
	vector<string> pieces;
};

#endif /* GAMEBOARD_H_ */
