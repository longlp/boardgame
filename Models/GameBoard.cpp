#include "GameBoard.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

string NumberToString(int Number) {
	ostringstream ss;
	ss << Number;
	return ss.str();
}

Game_Board::Game_Board() {
	srand(time(NULL));
	//add 10 pieces to make player choose from it
	pieces.insert(pieces.end(), "red    ");
	pieces.insert(pieces.end(), "blue   ");
	pieces.insert(pieces.end(), "green  ");
	pieces.insert(pieces.end(), "black  ");
	pieces.insert(pieces.end(), "white  ");
	pieces.insert(pieces.end(), "magneta");
	pieces.insert(pieces.end(), "cyan   ");
	pieces.insert(pieces.end(), "gray   ");
	pieces.insert(pieces.end(), "yellow ");
	pieces.insert(pieces.end(), "orange ");

	ifstream myfile("spaces.txt");
	string line;
	string price;
	//create 40 space
	for (int i = 0; i < 40; ++i) {
		getline(myfile, line);
		line = line.substr(0, line.size() - 1);
		getline(myfile, price);
//		price = price.substr(0, price.size() - 1);
		Space* s = new Space(line, atoi(price.c_str()));
		spaces.insert(spaces.end(), s);
	}
	myfile.close();
	//ask for number of player and create them
	int n;
	bool done = false;
	do {
		try {
			done = true;
			cout << "Enter number of player (2-4)\n";
			cin >> n;
			if (n < 2 || n > 4)
				done = false;
		} catch (exception & e) {
			done = false;
		}
	} while (!done);
	for (int i = 0; i < n; ++i) {
		done = false;
		int pn = 0;
		do {
			try {
				done = true;
				cout << "player " << (i + 1) << "\n";
				cout << "Choose piece color\n";
				for (int i = 0; i < pieces.size(); ++i) {
					cout << i << " " << pieces[i] << "\n";
				}
				cin >> pn;
				if (pn < 0 || pn >= pieces.size())
					done = false;
			} catch (exception & e) {
				done = false;
			}
		} while (!done);
		Player* p = new Player(0, pieces[pn]);
		players.insert(players.end(), p);
		pieces.erase(pieces.begin() + pn);
	}
}
void Game_Board::printBoard() {
	for (int i = 0; i < 11; ++i) {
		cout << "--------";
	}
	cout << "-\n";
	int count = 0;
	int lev[players.size()];
	for (int i = 20; i < 31; ++i) {
		cout << "|" << spaces[i]->getName();
		int tc = 0;
		for (int j = 0; j < players.size(); ++j) {
			if (players[j]->getPos() == i) {
				lev[j] = tc;
				tc++;
			}
		}
		if (tc > count)
			count = tc;
	}
	cout << "|\n";

	for (int i = 20; i < 31; ++i) {
		cout << "|" << spaces[i]->getOwner();
	}
	cout << "|\n";

	for (int i = 20; i < 31; ++i) {
		printf("|%7d", spaces[i]->getPrice());
	}
	cout << "|\n";

	for (int k = 0; k < count; ++k) {
		for (int i = 20; i < 31; ++i) {
			bool ok = false;
			for (int j = 0; j < players.size(); ++j) {
				if (players[j]->getPos() == i && lev[j] == k) {
					cout << "|" << players[j]->getPiece();
					ok = true;
					break;
				}
			}
			if (!ok)
				cout << "|       ";
		}
		cout << "|\n";
	}
	for (int i = 0; i < 11; ++i) {
		cout << "--------";
	}
	cout << "-\n";
	for (int i = 19, k = 0; i > 10; --i, k++) {
		count = 0;
		cout << "|" << spaces[i]->getName() << "|";
		cout << "       ";
		for (int j = 0; j < 8; ++j) {
			cout << "        ";
		}
		int tc = 0;
		for (int j = 0; j < players.size(); ++j) {
			if (players[j]->getPos() == i) {
				lev[j] = tc;
				tc++;
			}
		}
		if (tc > count)
			count = tc;

		cout << "|" << spaces[i + 12 + (2 * k)]->getName() << "|";
		cout << "\n";
		tc = 0;
		for (int j = 0; j < players.size(); ++j) {
			if (players[j]->getPos() == i + 12 + (2 * k)) {
				lev[j] = tc;
				tc++;
			}
		}
		if (tc > count)
			count = tc;
		cout << "|" << spaces[i]->getOwner() << "|";
		cout << "       ";
		for (int j = 0; j < 8; ++j) {
			cout << "        ";
		}
		cout << "|" << spaces[i + 12 + (2 * k)]->getOwner() << "|";
		cout << "\n";

		printf("|%7d|", spaces[i]->getPrice());
		cout << "       ";
		for (int j = 0; j < 8; ++j) {
			cout << "        ";
		}
		printf("|%7d|", spaces[i + 12 + (2 * k)]->getPrice());
		cout << "\n";

		for (int kk = 0; kk < count; ++kk) {
			bool ok = false;
			for (int j = 0; j < players.size(); ++j) {
				if (players[j]->getPos() == i && lev[j] == kk) {
					cout << "|" << players[j]->getPiece() << "|";
					ok = true;
					break;
				}
			}
			if (!ok)
				cout << "|       |";
			cout << "       ";
			for (int j = 0; j < 8; ++j) {
				cout << "        ";
			}
			ok = false;
			for (int j = 0; j < players.size(); ++j) {
				if (players[j]->getPos() == i + 12 + (2 * k) && lev[j] == kk) {
					cout << "|" << players[j]->getPiece() << "|";
					ok = true;
					break;
				}
			}
			if (!ok)
				cout << "|       |";
			cout << "\n";
		}
		if (i > 11) {
			cout << "---------";
			cout << "       ";
			for (int j = 0; j < 8; ++j) {
				cout << "        ";
			}
			cout << "---------\n";
		}
	}
	for (int i = 0; i < 11; ++i) {
		cout << "--------";
	}
	cout << "-\n";
	count = 0;
	for (int i = 10; i >= 0; --i) {
		cout << "|" << spaces[i]->getName();
		int tc = 0;
		for (int j = 0; j < players.size(); ++j) {
			if (players[j]->getPos() == i) {
				lev[j] = tc;
				tc++;
			}
		}
		if (tc > count)
			count = tc;
	}
	cout << "|\n";

	for (int i = 10; i >= 0; --i) {
		cout << "|" << spaces[i]->getOwner();
	}
	cout << "|\n";

	for (int i = 10; i >= 0; --i) {
		printf("|%7d", spaces[i]->getPrice());
	}
	cout << "|\n";

	for (int k = 0; k < count; ++k) {
		for (int i = 10; i >= 0; --i) {
			bool ok = false;
			for (int j = 0; j < players.size(); ++j) {
				if (players[j]->getPos() == i && lev[j] == k) {
					cout << "|" << players[j]->getPiece();
					ok = true;
					break;
				}
			}
			if (!ok)
				cout << "|       ";
		}
		cout << "|\n";
	}
	for (int i = 0; i < 11; ++i) {
		cout << "--------";
	}
	cout << "-\n";
	for (int k = 0; k < players.size(); ++k) {
		cout << players[k]->getPiece() << " player has "
				<< players[k]->getMoney() << "\n";
	}
}
void Game_Board::start() {
	//start game
	cout << "Game Started!\n";
	char rol;
	printBoard();
	while (true) {
		int i = 0;
		for (; i < players.size(); ++i) {
			cout << "\n";
			cout << players[i]->getPiece() << " turn\n";
			if (players[i]->getLostTurn() > 0) {
				cout << players[i]->getPiece() << " lost his turn\n";
				players[i]->setLostTurn(players[i]->getLostTurn() - 1);
				cout << "Enter any char to continue";
				cin >> rol;
				continue;
			}
			cout << "roll dice(r)\tleave game(any other char)";
			cin >> rol;
			if (rol != 'r' && rol != 'R') //leave or roll dice
					{
				cout << players[i]->getPiece() << " leave game\n";

				for (int ii = 0; ii < spaces.size(); ++i) {
					if (spaces[ii]->getOwner().compare(players[i]->getPiece())
							== 0)
						spaces[ii]->setOwner("No One ");
				}
				players.erase(players.begin() + i);
				i--;
				if (players.size() == 1) {
					cout << players[0]->getPiece() << " win\n";
					exit(0);
				}

				continue;
			}
			int oldPos = players[i]->getPos();
			cout << "rolling dice ..."
					<< players[i]->rollDice(spaces[oldPos]->is2XSpeed())
					<< "\n";
			cout << "Enter any char to continue";
			cin >> rol;
			printBoard();
			int newPos = players[i]->getPos();
			if (newPos < oldPos) {
				cout << players[i]->getPiece()
						<< " complete new round, take new 350$\n";
				players[i]->setMoney(players[i]->getMoney() + 350);
				cout << "Enter any char to continue";
				cin >> rol;
				printBoard();
			}
			if (spaces[newPos]->isChance()) {
				cout << "Chance\n";
				chance(&i);
				printBoard();
			} else if (spaces[newPos]->isChest()) {
				cout << "Chest\n";
				chest(&i);
				printBoard();
			} else if (spaces[newPos]->isPrison()) {
				cout << players[i]->getPiece() << " fall in prison\n";
				if (players[i]->getMoney() >= 50) {
					cout << players[i]->getPiece() << " pay 50$\n";
					players[i]->setMoney(players[i]->getMoney() - 50);
				} else {
					cout << players[i]->getPiece() << " lost his next turn\n";
					players[i]->setLostTurn(players[i]->getLostTurn() + 1);
				}
				cout << "Enter any char to continue";
				cin >> rol;
				printBoard();
			} else if (!spaces[newPos]->isPark()) {
				if (spaces[newPos]->isFree()
						&& players[i]->getMoney()
								>= spaces[newPos]->getPrice()) {
					cout << "buy " << spaces[newPos]->getName()
							<< " yes (y)\tno(any other char)";
					cin >> rol;
					if (rol == 'y' || rol == 'Y') {
						spaces[newPos]->setOwner(players[i]->getPiece());
						players[i]->setMoney(
								players[i]->getMoney()
										- spaces[newPos]->getPrice());
						if (!spaces[newPos]->isUp()
								&& players[i]->getMoney()
										>= spaces[newPos]->getPrice()) {
							cout << "upgrade " << spaces[newPos]->getName()
									<< ", it'll double price and fees too yes (y)\tno(any other char)";
							cin >> rol;

							if (rol == 'y' || rol == 'Y') {
								players[i]->setMoney(
										players[i]->getMoney()
												- spaces[newPos]->getPrice());
								spaces[newPos]->upgrade();
							}
						}
						printBoard();
					}
				} else {
					if (spaces[newPos]->getOwner().compare(
							players[i]->getPiece()) == 0) {
						if (!spaces[newPos]->isUp()
								&& players[i]->getMoney()
										>= spaces[newPos]->getPrice()) {
							cout << "upgrade " << spaces[newPos]->getName()
									<< ", it'll double price and fees too yes (y)\tno(any other char)";
							cin >> rol;

							if (rol == 'y' || rol == 'Y') {
								players[i]->setMoney(
										players[i]->getMoney()
												- spaces[newPos]->getPrice());
								spaces[newPos]->upgrade();
								printBoard();
							}
						}
						cout << "sell " << spaces[newPos]->getName()
								<< ", to bank yes (y)\tno(any other char)";
						cin >> rol;

						if (rol == 'y' || rol == 'Y') {
							players[i]->setMoney(
									players[i]->getMoney()
											+ spaces[newPos]->getPrice());
							spaces[newPos]->setOwner("No One ");
							printBoard();
						}
					} else {
						for (int l = 0; l < players.size(); ++l) {
							if (l != i) {
								if (players[l]->getPiece().compare(
										spaces[newPos]->getOwner()) == 0) {
									cout << "You have to pay "
											<< (spaces[newPos]->getPrice() / 10)
											<< "$ to " << players[l]->getPiece()
											<< "player\n";
									if (players[i]->getMoney()
											>= spaces[newPos]->getPrice()
													/ 10) {
										players[i]->setMoney(
												players[i]->getMoney()
														- (spaces[newPos]->getPrice()
																/ 10));
										players[l]->setMoney(
												players[l]->getMoney()
														+ (spaces[newPos]->getPrice()
																/ 10));

										cout << "Enter any char to continue";
										cin >> rol;
										printBoard();
									} else {
										cout
												<< "You don't have enough money, you lose\n";
										players.erase(players.begin() + i);
										i--;
										if (players.size() == 1) {
											cout << players[0]->getPiece()
													<< " win\n";
											exit(0);
										}
									}
								}
							}
						}
					}
				}

			}
		}

		if (i < players.size()) {
			cout << "Sure exit? yes(y)\t no(any other char)";
			cin >> rol;
			if (rol == 'y' || rol == 'Y') //exit or roll dice
				break;
		}

	}
}

void Game_Board::chest(int* i) {
	int rdm = rand() % 7;
	switch (rdm) {
	case 0:
		cout << "Congratulations, you win a case against the bank, take 150$\n";
		players[*i]->setMoney(players[*i]->getMoney() + 150);
		break;
	case 1:
		cout << "You throw rubbish in the street, pay 50$ as a penalty$\n";
		players[*i]->setMoney(players[*i]->getMoney() - 50);
		break;
	case 2:
		cout << "You have an accident with your car, pay 40$ as a penalty$\n";
		players[*i]->setMoney(players[*i]->getMoney() - 40);
		break;
	case 3:
		cout << "You try to escape from prison, go to prison now\n";
		players[*i]->setPos(30);
		players[*i]->setLostTurn(players[*i]->getLostTurn() + 1);
		break;
	case 4:
		cout << "You lost a case, pay 20$ lawyer fees\n";
		players[*i]->setMoney(players[*i]->getMoney() - 20);
		break;
	case 5:
		cout << "You win a prize, take 100$\n";
		players[*i]->setMoney(players[*i]->getMoney() + 100);
		break;
	case 6:
		cout
				<< "You had been accused, but your innocence appeared, take 200$ as amends\n";
		players[*i]->setMoney(players[*i]->getMoney() + 200);
		break;
	}
	if (players[*i]->getMoney() < 0) {
		cout << "You don't have enough money, you lose\n";
		players.erase(players.begin() + *i);
		(*i)--;
		if (players.size() == 1) {
			cout << players[0]->getPiece() << " win\n";
			exit(0);
		}
	}
	char rol;
	cout << "Enter any char to continue";
	cin >> rol;
}
void Game_Board::chance(int* i) {
	int rdm = rand() % 7;
	switch (rdm) {
	case 0:
		cout << "You're very naughty, pay 50$\n";
		players[*i]->setMoney(players[*i]->getMoney() - 50);
		break;
	case 1:
		cout << "You win a big prize, take 350$\n";
		players[*i]->setMoney(players[*i]->getMoney() + 350);
		break;
	case 2:
		cout << "You've got a new baby take 100$ as a gift\n";
		players[*i]->setMoney(players[*i]->getMoney() + 100);
		break;
	case 3:
		cout << "You're very kind, you payed 150 for father-less children\n";
		players[*i]->setMoney(players[*i]->getMoney() - 150);
		break;
	case 4:
		cout << "It is your birthday take 50 as a gift\n";
		players[*i]->setMoney(players[*i]->getMoney() + 50);
		break;
	case 5:
		cout << "You pay 25$ each for your four children in school in fees\n";
		players[*i]->setMoney(players[*i]->getMoney() - 100);
		break;
	case 6:
		cout
				<< "You win a very big prize, but you have to pay 30$ to take it\n";
		players[*i]->setMoney(players[*i]->getMoney() - 30);
		break;
	}
	if (players[*i]->getMoney() < 0) {
		cout << "You don't have enough money, you lose\n";
		players.erase(players.begin() + *i);
		(*i)--;
		if (players.size() == 1) {
			cout << players[0]->getPiece() << " win\n";
			exit(0);
		}
	}
	char rol;
	cout << "Enter any char to continue";
	cin >> rol;
}

