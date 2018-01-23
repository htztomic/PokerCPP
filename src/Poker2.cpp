//============================================================================
// Name        : Poker2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//============================================================================
// Name        : Poker.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <stdlib.h>
#include <map>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class Cards {
public:
	int cardNumber;
	int suits;
	Cards(int a, int suit) {
		cardNumber = (a + 2);
		suits = suit;
	}

};
class Deck {
public:
	vector<Cards> deckOfCards;
	Deck() {
		for (int i = 0; i < 13; i++) {
			for (int j = 0; j < 4; j++) {
				Cards newCard(i, j);
				deckOfCards.push_back(newCard);
			}
		}
	}

};
class Dealers {
private:
	int amountOfPlayers;
	vector<int> player;
	vector<vector<Cards> > players;
	Deck NewDeck;
	int bc;
	vector<string> playersNames;
public:
	Dealers(int NumOfP, vector<string> Name) {
		amountOfPlayers = NumOfP;
		bc = 52;
		playersNames = Name;
		for (int i = 0; i < NumOfP; i++) {
			player.push_back(0);
		}
	}
	void handOutHands() {
		vector<Cards> checking;
		for (int p = 0; p < 5; p++) {
			if(p<=1){
			Cards k(3+p, 0);
			checking.push_back(k);
			}
				else{
			Cards k(5,1);
			checking.push_back(k);
			}
		}
		players.push_back(checking);
		for (int i = 0; i < (amountOfPlayers - 1); i++) {
			vector<Cards> handing;

			for (int j = 0; j < 5; j++) {
				int ran = rand() % bc;
				handing.push_back(NewDeck.deckOfCards[ran]);
				NewDeck.deckOfCards.erase(
						NewDeck.deckOfCards.begin() + (ran - 1));
				bc--;
			}
			players.push_back(handing);

		}
	}
	void checkForRoyalFlush() {
		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			int check = 0;
			int check2 = 0;
			for (int b = 0; b < 5; b++) {
				if (checking[0].suits == checking[b].suits) {
					check2++;
				}
			}
			if (check2 == 5) {
				for (int j = 0; j < 5; j++) {
					if (checking[j].cardNumber == 14) {
						check++;
					} else if (checking[j].cardNumber == 13) {
						check++;
					} else if (checking[j].cardNumber == 12) {
						check++;
					} else if (checking[j].cardNumber == 11) {
						check++;
					} else if (checking[j].cardNumber == 10) {
						check++;
					}
				}

			}
			if (check == 5) {
				player[i] = 9;
			}

		}

	}
	void checkForStraightFlush() {
		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			map<int, int> count2;
						map<int, int>::iterator ptr;
						int check = 0;
						int check2 = 0;
						int min = 100;
			for (int b = 0; b < 5; b++) {
				if (checking[b].cardNumber < min) {
					min = checking[b].cardNumber;
				}
			}
			for (int b = 0; b < 5; b++) {
				if (checking[0].suits == checking[b].suits) {
					check2++;
				}
			}
			if (check2 == 5) {
							for (int b = 0; b < 5; b++) {
								count2[checking[b].cardNumber]++;
							}
							for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
								if (ptr->first == min) {
									check++;
								}
								if (ptr->first == (min + 1)) {
									check++;
								}
								if (ptr->first == (min + 2)) {
									check++;
								}
								if (ptr->first == (min + 3)) {
									check++;
								}
								if (ptr->first == (min + 4)) {
									check++;
								}
							}
			}
			if (check == 5) {
				player[i] = 8;
			}

		}

	}
	void checkForFourOfAKind() {
		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			int check = 0;
			map<int, int> count2;
			map<int, int>::iterator ptr;
			for (int b = 0; b < 5; b++) {
				count2[checking[b].cardNumber]++;

			}
			for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
				if (ptr->second == 4) {
					check++;

				}
			}

			if (check == 1) {
				player[i] = 7;
			}

		}
	}
	void displayHands() {
		checkForOnePair();
		checkForTwoPairs();
		checkForThreeOfAKind();
		checkForStraight();
		checkForFlush();
		checkForFullHouse();
		checkForFourOfAKind();
		checkForStraightFlush();
		checkForRoyalFlush();
		string values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J",
				"Q", "K", "A"

		};
		string type[] = { "no pair", "one pair", "two pairs", "three pairs",
				"a straight", "a flush", "a full house", "a four of a kind",
				"a straight flush,",
						"a royal flush"

		};
		string heart[] = { "|  _  _  |", "| ( \\/ ) |", "|  \\  /  |",
				"|   \\/   |" };
		string diamond[] = { "|   /\\   |", "|  /  \\  |", "|  \\  /  |",
				"|   \\/   |" };


		string spades[] = { "|   /\\   |", "|  /  \\  |", "| (    ) |",
				"|   \\/   |" };
		string clubs[] = { "|    _   |", "|  _(_)_ |", "| (_)+(_)|",
				"|    |   |" };

		for (int i = 0; i < amountOfPlayers; i++) {
			cout << playersNames[i] << "'s hand:" << endl;
			vector<Cards> checking = players[i];
			string a[4];
			string b[4];
			string c[4];
			string d[4];
			string e[4];
			for (int j = 0; j < 5; j++) {
				if (j == 0) {
					if (checking[j].suits == 0) {
						a[0] = diamond[0];
						a[1] = diamond[1];
						a[2] = diamond[2];
						a[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						a[0] = clubs[0];
						a[1] = clubs[1];
						a[2] = clubs[2];
						a[3] = clubs[3];

					}
					if (checking[j].suits == 2) {
						a[0] = heart[0];
						a[1] = heart[1];
						a[2] = heart[2];
						a[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						a[0] = spades[0];
						a[1] = spades[1];
						a[2] = spades[2];
						a[3] = spades[3];

					}

				}
				if (j == 1) {
					if (checking[j].suits == 0) {
						b[0] = diamond[0];
						b[1] = diamond[1];
						b[2] = diamond[2];
						b[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						b[0] = clubs[0];
						b[1] = clubs[1];
						b[2] = clubs[2];
						b[3] = clubs[3];
					}
					if (checking[j].suits == 2) {
						b[0] = heart[0];
						b[1] = heart[1];
						b[2] = heart[2];
						b[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						b[0] = spades[0];
						b[1] = spades[1];
						b[2] = spades[2];
						b[3] = spades[3];
					}

				}
				if (j == 2) {
					if (checking[j].suits == 0) {
						c[0] = diamond[0];
						c[1] = diamond[1];
						c[2] = diamond[2];
						c[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						c[0] = clubs[0];
						c[1] = clubs[1];
						c[2] = clubs[2];
						c[3] = clubs[3];
					}
					if (checking[j].suits == 2) {
						c[0] = heart[0];
						c[1] = heart[1];
						c[2] = heart[2];
						c[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						c[0] = spades[0];
						c[1] = spades[1];
						c[2] = spades[2];
						c[3] = spades[3];
					}

				}
				if (j == 3) {
					if (checking[j].suits == 0) {
						d[0] = diamond[0];
						d[1] = diamond[1];
						d[2] = diamond[2];
						d[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						d[0] = clubs[0];
						d[1] = clubs[1];
						d[2] = clubs[2];
						d[3] = clubs[3];
					}
					if (checking[j].suits == 2) {
						d[0] = heart[0];
						d[1] = heart[1];
						d[2] = heart[2];
						d[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						d[0] = spades[0];
						d[1] = spades[1];
						d[2] = spades[2];
						d[3] = spades[3];
					}

				}
				if (j == 4) {
					if (checking[j].suits == 0) {
						e[0] = diamond[0];
						e[1] = diamond[1];
						e[2] = diamond[2];
						e[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						e[0] = clubs[0];
						e[1] = clubs[1];
						e[2] = clubs[2];
						e[3] = clubs[3];
					}
					if (checking[j].suits == 2) {
						e[0] = heart[0];
						e[1] = heart[1];
						e[2] = heart[2];
						e[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						e[0] = spades[0];
						e[1] = spades[1];
						e[2] = spades[2];
						e[3] = spades[3];
					}

				}
			}
			cout << " ________" << "     " << " ________" << "     "
					<< " ________" << "     " << " ________" << "     "
					<< " ________" << endl;
			cout << "|" << left << setw(2) << values[checking[0].cardNumber - 2]
					<< "      |" << "    " << "|" << left << setw(2)
					<< values[checking[1].cardNumber - 2] << "      |" << "    "
					<< "|" << left << setw(2)
					<< values[checking[2].cardNumber - 2] << "      |" << "    "
					<< "|" << left << setw(2)
					<< values[checking[3].cardNumber - 2] << "      |" << "    "
					<< "|" << left << setw(2)
					<< values[checking[4].cardNumber - 2] << "      |" << endl;
			cout << a[0] << "    " << b[0] << "    " << c[0] << "    " << d[0]
					<< "    " << e[0] << endl;
			cout << a[1] << "    " << b[1] << "    " << c[1] << "    " << d[1]
					<< "    " << e[1] << endl;
			cout << a[2] << "    " << b[2] << "    " << c[2] << "    " << d[2]
					<< "    " << e[2] << endl;
			cout << a[3] << "    " << b[3] << "    " << c[3] << "    " << d[3]
					<< "    " << e[3] << endl;
			cout << "|      " << right << setw(2)
					<< values[checking[0].cardNumber - 2] << "|" << "    "
					<< "|      " << right << setw(2)
					<< values[checking[1].cardNumber - 2] << "|" << "    "
					<< "|      " << right << setw(2)
					<< values[checking[2].cardNumber - 2] << "|" << "    "
					<< "|      " << right << setw(2)
					<< values[checking[3].cardNumber - 2] << "|" << "    "
					<< "|      " << right << setw(2)
					<< values[checking[4].cardNumber - 2] << "|" << endl;
			cout << "`--------`" << "    " << "`--------`" << "    "
					<< "`--------`" << "    " << "`--------`" << "    "
					<< "`--------`" << endl;

			cout << playersNames[i] << " has " << type[player[i]] << endl;
		}
	}

	void checkForFullHouse() {
		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			int check = 0;
			int check2 = 0;
			map<int, int> count2;
			map<int, int>::iterator ptr;
			for (int b = 0; b < 5; b++) {
				count2[checking[b].cardNumber]++;

			}
			for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
				if (ptr->second == 3) {
					check++;

				}
			}
			for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
				if (ptr->second == 2) {
					check2++;
				}
			}

			if (check == 1 && check2 == 1) {
				player[i] = 6;
			}

		}
	}
	void checkForFlush() {
		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			int check = 0;
			map<int, int> count;
			map<int, int>::iterator ptr;
			for (int b = 0; b < 5; b++) {
				count[checking[b].suits]++;

			}
			for (ptr = count.begin(); ptr != count.end(); ptr++) {
				if (ptr->second == 5) {
					check++;

				}
			}
			if (check == 1) {
				player[i] = 5;
			}

		}

	}
	void checkForStraight() {
		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			map<int, int> count2;
			map<int, int>::iterator ptr;
			int check = 0;
			int min = 100;
			for (int b = 0; b < 5; b++) {
				if (checking[b].cardNumber < min) {
					min = checking[b].cardNumber;
				}
			}
			for (int b = 0; b < 5; b++) {
				count2[checking[b].cardNumber]++;

			}
			for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
				if (ptr->first == min) {
					check++;
				}
				if (ptr->first == (min + 1)) {
					check++;
				}
				if (ptr->first == (min + 2)) {
					check++;
				}
				if (ptr->first == (min + 3)) {
					check++;
				}
				if (ptr->first == (min + 4)) {
					check++;
				}
			}
			if (check == 5) {
				player[i] = 4;
			}

		}
	}
	void checkForThreeOfAKind() {
		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			int check = 0;
			int check2 = 0;
			map<int, int> count2;
			map<int, int>::iterator ptr;
			for (int b = 0; b < 5; b++) {
				count2[checking[b].cardNumber]++;

			}
			for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
				if (ptr->second == 3) {
					check++;
				}
				if (ptr->second == 2) {
					check2++;
				}
			}
			if (check == 1 & check2 == 0) {
				player[i] = 3;
			}
		}
	}
	void checkForTwoPairs() {
		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			int check = 0;
			map<int, int> count2;
			map<int, int>::iterator ptr;
			for (int b = 0; b < 5; b++) {
				count2[checking[b].cardNumber]++;

			}
			for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
				if (ptr->second == 2) {
					check++;

				}
			}
			if (check == 2) {
				player[i] = 2;
			}
		}

	}

	void checkForOnePair() {

		for (int i = 0; i < amountOfPlayers; i++) {
			vector<Cards> checking = players[i];
			int check = 0;
			map<int, int> count2;
			map<int, int>::iterator ptr;
			for (int b = 0; b < 5; b++) {
				count2[checking[b].cardNumber]++;

			}
			for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
				if (ptr->second == 2) {
					check++;
				}
			}
			if (check == 1) {
				player[i] = 1;
			}
		}

	}

	void discardACard() {
		char checker;
		int discardAmount;
		string values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J",
				"Q", "K", "A"

		};
		string type[] = { "no pair", "one pair", "two pairs", "three pairs",
				"a straight", "a flush", "a full house", "a four of a kind",
				"a straight flush,",
						"a royal flush"

		};
		string heart[] = { "|  _  _  |", "| ( \\/ ) |", "|  \\  /  |",
				"|   \\/   |" };
		string diamond[] = { "|   /\\   |", "|  /  \\  |", "|  \\  /  |",
				"|   \\/   |" };

		string spades[] = { "|   /\\   |", "|  /  \\  |", "| (    ) |",
				"|   \\/   |" };
		string clubs[] = { "|    _   |", "|  _(_)_ |", "| (_)+(_)|",
				"|    |   |" };

		for (int i = 0; i < amountOfPlayers; i++) {
			cout << playersNames[i] << "'s hand:" << endl;
			vector<Cards> checking = players[i];
			string a[4];
			string b[4];
			string c[4];
			string d[4];
			string e[4];
			for (int j = 0; j < 5; j++) {
				if (j == 0) {
					if (checking[j].suits == 0) {
						a[0] = diamond[0];
						a[1] = diamond[1];
						a[2] = diamond[2];
						a[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						a[0] = clubs[0];
						a[1] = clubs[1];
						a[2] = clubs[2];
						a[3] = clubs[3];

					}
					if (checking[j].suits == 2) {
						a[0] = heart[0];
						a[1] = heart[1];
						a[2] = heart[2];
						a[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						a[0] = spades[0];
						a[1] = spades[1];
						a[2] = spades[2];
						a[3] = spades[3];

					}

				}
				if (j == 1) {
					if (checking[j].suits == 0) {
						b[0] = diamond[0];
						b[1] = diamond[1];
						b[2] = diamond[2];
						b[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						b[0] = clubs[0];
						b[1] = clubs[1];
						b[2] = clubs[2];
						b[3] = clubs[3];
					}
					if (checking[j].suits == 2) {
						b[0] = heart[0];
						b[1] = heart[1];
						b[2] = heart[2];
						b[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						b[0] = spades[0];
						b[1] = spades[1];
						b[2] = spades[2];
						b[3] = spades[3];
					}

				}
				if (j == 2) {
					if (checking[j].suits == 0) {
						c[0] = diamond[0];
						c[1] = diamond[1];
						c[2] = diamond[2];
						c[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						c[0] = clubs[0];
						c[1] = clubs[1];
						c[2] = clubs[2];
						c[3] = clubs[3];
					}
					if (checking[j].suits == 2) {
						c[0] = heart[0];
						c[1] = heart[1];
						c[2] = heart[2];
						c[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						c[0] = spades[0];
						c[1] = spades[1];
						c[2] = spades[2];
						c[3] = spades[3];
					}

				}
				if (j == 3) {
					if (checking[j].suits == 0) {
						d[0] = diamond[0];
						d[1] = diamond[1];
						d[2] = diamond[2];
						d[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						d[0] = clubs[0];
						d[1] = clubs[1];
						d[2] = clubs[2];
						d[3] = clubs[3];
					}
					if (checking[j].suits == 2) {
						d[0] = heart[0];
						d[1] = heart[1];
						d[2] = heart[2];
						d[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						d[0] = spades[0];
						d[1] = spades[1];
						d[2] = spades[2];
						d[3] = spades[3];
					}

				}
				if (j == 4) {
					if (checking[j].suits == 0) {
						e[0] = diamond[0];
						e[1] = diamond[1];
						e[2] = diamond[2];
						e[3] = diamond[3];

					}
					if (checking[j].suits == 1) {
						e[0] = clubs[0];
						e[1] = clubs[1];
						e[2] = clubs[2];
						e[3] = clubs[3];
					}
					if (checking[j].suits == 2) {
						e[0] = heart[0];
						e[1] = heart[1];
						e[2] = heart[2];
						e[3] = heart[3];

					}
					if (checking[j].suits == 3) {
						e[0] = spades[0];
						e[1] = spades[1];
						e[2] = spades[2];
						e[3] = spades[3];
					}

				}
			}
			cout << " ________" << "     " << " ________" << "     "
					<< " ________" << "     " << " ________" << "     "
					<< " ________" << endl;
			cout << "|" << left << setw(2) << values[checking[0].cardNumber - 2]
					<< "      |" << "    " << "|" << left << setw(2)
					<< values[checking[1].cardNumber - 2] << "      |" << "    "
					<< "|" << left << setw(2)
					<< values[checking[2].cardNumber - 2] << "      |" << "    "
					<< "|" << left << setw(2)
					<< values[checking[3].cardNumber - 2] << "      |" << "    "
					<< "|" << left << setw(2)
					<< values[checking[4].cardNumber - 2] << "      |" << endl;
			cout << a[0] << "    " << b[0] << "    " << c[0] << "    " << d[0]
					<< "    " << e[0] << endl;
			cout << a[1] << "    " << b[1] << "    " << c[1] << "    " << d[1]
					<< "    " << e[1] << endl;
			cout << a[2] << "    " << b[2] << "    " << c[2] << "    " << d[2]
					<< "    " << e[2] << endl;
			cout << a[3] << "    " << b[3] << "    " << c[3] << "    " << d[3]
					<< "    " << e[3] << endl;
			cout << "|      " << right << setw(2)
					<< values[checking[0].cardNumber - 2] << "|" << "    "
					<< "|      " << right << setw(2)
					<< values[checking[1].cardNumber - 2] << "|" << "    "
					<< "|      " << right << setw(2)
					<< values[checking[2].cardNumber - 2] << "|" << "    "
					<< "|      " << right << setw(2)
					<< values[checking[3].cardNumber - 2] << "|" << "    "
					<< "|      " << right << setw(2)
					<< values[checking[4].cardNumber - 2] << "|" << endl;
			cout << "`--------`" << "    " << "`--------`" << "    "
					<< "`--------`" << "    " << "`--------`" << "    "
					<< "`--------`" << endl;

			cout << playersNames[i] << " has " << type[player[i]] << endl;
			cout << "Would you like to discard a few cards?(Y or N): ";
			cin >> checker;
			string nd[] = { "first", "second", "third", "fourth", "fifth"

			};
			int che;
			vector<int> whichCard;
			while (checker == 'Y' || checker == 'y') {
				cout << "How many cards would you like to discard?: ";
				cin >> discardAmount;
				for (int i = 0; i < discardAmount; i++) {
					cout << "Please enter " << nd[i]
							<< " card's position from 1-5 and starting left to right: ";
					cin >> che;
					whichCard.push_back(che);
				}
				for (int j = 0; j < discardAmount; j++) {
					int ran = rand() % bc;
					players[i].erase(players[i].begin() + (whichCard[j] - 1));
					players[i].insert(players[i].begin() + (whichCard[j] - 1),
							NewDeck.deckOfCards[ran]);
					NewDeck.deckOfCards.erase(
							NewDeck.deckOfCards.begin() + (ran - 1));
					bc--;
				}
				cout << "Thank You, you're cards have been discarded" << endl;
				checker = 'N';

			}

		}
	}

	void checkForWinners() {
		int winner = 0;
		int check2 = 0;
		int max2 = 0;
		int max = 0;
		int amountOfWinners;
		int highest = 0;

		map<int, int> count2;
		map<int, int>::iterator ptr;
		for (int b = 0; b < amountOfPlayers; b++) {
			count2[player[b]]++;
		}
		for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
			if (ptr->first >= max2) {
				max2 = ptr->first;
			}
		}

		for (ptr = count2.begin(); ptr != count2.end(); ptr++) {
			if (ptr->second > 1) {
				if (ptr->first >= max) {
					max = ptr->first;
					amountOfWinners = ptr->second;
				}
			}
		}
		if (max2 != max) {
			for (int i = 0; i < amountOfPlayers; i++) {
				if (player[i] > highest) {
					winner = i;
					highest = player[i];
				}
			}
			cout << playersNames[winner] << " is the winner!!" << endl;
		} else {
			cout << "The Winners are ";
			for (int i = 0; i < amountOfPlayers; i++) {

				if (player[i] == max) {
					if (check2 == (amountOfWinners - 1)) {
						cout << "and " << playersNames[i] << endl;
					} else {
						cout << playersNames[i] << " ";
						check2++;
					}
				}
			}
		}

	}

}
;

int main() {
	char check;
	srand(time(NULL));
	int amountOfPlayers;

	cout
			<< " _       __     __                             __           ____        __                __ "
			<< endl;
	cout
			<< "| |     / /__  / /________  ____ ___  ___     / /_____     / __ \\____  / /_____  _____   / / "
			<< endl;
	cout
			<< "| | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\   / __/ __ \\   / /_/ / __ \\/ //_/ _ \\/ ___/  / /  "
			<< endl;
	cout
			<< "| |/ |/ /  __/ / /__/ /_/ / / / / / /  __/  / /_/ /_/ /  / ____/ /_/ / ,< /  __/ /     /_/  "
			<< endl;
	cout
			<< "|__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/   \\__/\\____/  /_/    \\____/_/|_|\\___/_/     (_)  "
			<< endl;

	cout << endl;
	cout << "                   __" << endl;
	cout << "             _..-''--'----_." << endl;
	cout << "           ,''.-''| .---/ _`-." << endl;
	cout << "         ,' \\ \\  ;| | ,/ / `-._`-." << endl;
	cout << "       ,' ,',\\ \\( | |// /,-._  / /" << endl;
	cout << "       ;.`. `,\\ \\`| |/ / |   )/ /" << endl;
	cout << "      / /`_`.\\_\\ \\| /_.-.'-''/ /" << endl;
	cout << "     / /_|_:.`. \\ |;'`..')  / /" << endl;
	cout << "     `-._`-._`.`.;`.\\  ,'  / /" << endl;
	cout << "         `-._`.`/    ,'-._/ /" << endl;
	cout << "           : `-/     \\`-.._/" << endl;
	cout << "           |  :      ;._ (" << endl;
	cout << "           :  |      \\  `\\" << endl;
	cout << "            \\         \\   |" << endl;
	cout << "             :        :   ;" << endl;
	cout << "             |           /" << endl;
	cout << "             ;         ,'" << endl;
	cout << "            /         /" << endl;
	cout << "           /         /" << endl;
	cout << "                    / " << endl;

	cout << "Do you wish to play poker or quit(p or q)? ";
	cin >> check;
	while (check != 'q' && check == 'p') {
		vector<string> playerNames;
		cout << "How many players are playing? ";
		cin >> amountOfPlayers;
		while (amountOfPlayers > 5 || amountOfPlayers < 2) {
			cout << "Only 2-5 People can play, Please enter again: ";
			cin >> amountOfPlayers;
		}
		string names;
		for (int i = 0; i < amountOfPlayers; i++) {
			cout << "Enter player name:";
			cin >> names;
			playerNames.push_back(names);
		}
		Dealers Game(amountOfPlayers, playerNames);
		Game.handOutHands();
		Game.checkForOnePair();
		Game.checkForTwoPairs();
		Game.checkForThreeOfAKind();
		Game.checkForStraight();
		Game.checkForFlush();
		Game.checkForFullHouse();
		Game.checkForFourOfAKind();
		Game.checkForStraightFlush();
		Game.checkForRoyalFlush();
		Game.discardACard();
		Game.displayHands();
		Game.checkForWinners();

		cout << "Do you wish to play poker or quit(p or q)? ";
		cin >> check;

	}
	return 0;
}


