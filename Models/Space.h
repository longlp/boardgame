/*
 * Space.h
 * Space class for first phase
 * will be edited in second phase by adding more
 * information like cost (if player will buy it)
 * and fees (if player stop in it)
 */

#ifndef SPACE_H_
#define SPACE_H_
#include <string>
using namespace std;

class Space {
public:
	/**
	 * constructor
	 */
	Space();
	/**
	 * constructor
	 * @param name unique name for each space
	 */
	Space(string name, int price);
	/**
	 * setName setter method for name
	 * @param name unique name for each space
	 */
	void setName(string name);
	/**
	 * getName getter method for name
	 * @return name of space
	 */
	string getName();
	string getOwner();
	void setOwner(string name);
	int getPrice();
	void upgrade();
	bool isChance();
	bool isChest();
	bool isPrison();
	bool is2XSpeed();
	bool isPark();
	bool isFree();
	bool isUp();
private:
	//unique name for every space
	string name;
	string owner;
	int price;
	bool up;
};

#endif /* SPACE_H_ */
