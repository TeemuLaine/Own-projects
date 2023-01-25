#include <iostream>
#include <time.h>
#include <conio.h>
#include <string>
#include <sstream>

using namespace std;

void welcome();
int playerCount();
int rollOption();
string playerNames();
void printChart(string*, string*,int**, int, bool**);
void rollDice(int**, string*, int, string*, bool**, int);
bool checkCompatibility(int, int*);
void fillScore(int, int*, int**, bool, int, int);
int totalPoints(int**, int, int);
void printWinner(string*, int**, int);
int nameCheck(string, int);
bool integerCheck(int);


int main() {
	srand(time(0));
	string rows[16] = {
	"Ones",
	"Twos",
	"Threes",
	"Fours",
	"Fives",
	"Sixes",
	"Sum",
	"Bonus",
	"Three of a kind",
	"Four of a kind",
	"Full House",
	"Small Straight",
	"Large Straight",
	"Chance",
	"YAHTZEE",
	"TOTAL SCORE"
	};
	welcome();
	int players = playerCount();
	int* score = new int[16 * players];
	bool* used = new bool[16 * players];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < players; j++) {
			*(score + i*players + j) = 0;
			*(used + i*players +j) = false;
		}
	}
	string* names = new string[players];
	int roundCount = 13 * players;
	int playerNumber = 0;
	for (int i = 0; i < players; i++) {
		names[i] = playerNames();
	}
	for (int i = 0; i < roundCount; i++) {
		if (playerNumber == players) {
			playerNumber = 0;
		}
		printChart(names, rows, &score, players, &used);
		rollDice(&score, rows, playerNumber, names, &used, players);
		playerNumber++;
	}
	printChart(names, rows, &score, players, &used);
	printWinner(names, &score, players);

	return 0;
}

void welcome() {
	cout << "Welcome to C++ yahtzee. " << endl;
}

int playerCount() {
	int players = 0;
			cout << "How many players?" << endl;
			do {
				cin >> players;
			} while (integerCheck(players));
	return players;
}

string playerNames() {
	string name;
	cout << "Input player name: ";
	cin >> name;

	return name;
}


void printChart(string* names, string* rows, int** score, int players, bool** used) {
	string* player = new string[players];
	cout << "\t \t";
	for (int i = 0; i < players; i++) {
		cout << names[i] << "\t";
	}
	cout << endl;
		for (int i = 0; i < 16; i++) {
			if (i == 0 || i == 6 || i == 8 || i == 15) {
				
				cout << "-----------------";
				for (int a = 0; a < players-1; a++) {
					cout << "---------";
				}
				cout << endl;
			}
			if (i < 8 || (i > 12 && i != 15)) {
				cout << rows[i] << "\t";
				for (int a = 0; a < players; a++) {
					if (*(*used + i*players + a) == true || i == 6 || i == 7 || i == 15) {
						std::ostringstream address;
						address << *(*score + i*players + a);
						player[a] = address.str();
					}
					else player[a] = "-";
					cout << "\t" << player[a];
					if (a == players - 1)
						cout << endl;
				}
			}
			else{
				cout << rows[i];
				for (int a = 0; a < players; a++) {
					if (*(*used + i*players + a) == true || i == 6 || i == 7 ||i == 15) {
						std::ostringstream address;
						address << *(*score + i*players + a);
						player[a] = address.str();
					}
					else player[a] = "-";
					cout << "\t" << player[a];
					if (a == players - 1)
						cout << endl;
				}
			}
		
	}
	cout << endl;
}

void rollDice(int** score, string* rows, int playerNumber, string* names, bool** used, int players) {
	int option;
	int dice[5] = {4,3,6,5,5};
	bool hold[5] = { false };
	int counter = 0;
	int taken = 5;
	bool rollAgain = true;
	cout << names[playerNumber] << ", roll dice with any key" << endl << endl;
	_getch();
	while (rollAgain) {
		for (int i = 0; i < 5; i++) {
			if (!hold[i]) {
				dice[i] = 1 + rand() % 6;
			}
		}
		for (int i = 0; i < 5; i++) {
			cout << dice[i] << " ";
		}
		cout << endl << endl;
		
		if (counter != 2) {
			option = rollOption();
		}
		else
			option = 1;
		if (option == 1) {
			int temp; // sort from largest to smallest;
			for (int i = 0; i < 5; i++) {
				for (int j = i + 1; j < 5; j++)	{
					if (dice[i] > dice[j])
					{
						temp = dice[i];
						dice[i] = dice[j];
						dice[j] = temp;
					}
				}
			}
			string placement;
			bool match = false;
			bool notfound = true;
			bool usedRow = true;
			while (notfound || usedRow) {
				cout << "Where would you like to place your score?" << endl;
				rollAgain = false;
				usedRow = false;
				do {
					getline(cin, placement);
				} while (placement == "");
				for (int i = 0; i < 16; i++) {
					if (i != 6 && i != 7 && i != 15) {
						if ((tolower(placement[0]) == tolower(rows[i][0]) && tolower(placement[1])==tolower(rows[i][1]))) {
							i = nameCheck(placement, i);
							notfound = false;
							if (*(*used + i*players + playerNumber) == false) {
								match = checkCompatibility(i, dice);
								fillScore(i, dice, score, match, playerNumber, players);
								*(*score + 15*players + playerNumber) = totalPoints(score, playerNumber, players);
								*(*used + i*players + playerNumber) = true;
								break;
							}
							else {
								cout << "You've already used that slot!" << endl;
								usedRow = true;
								break;
							}
						}
					}
				}
				if (notfound) {
					cout << "Matching row not found, try again." << endl;
				}
			}
		}
		if (option == 2) {
			rollAgain = true;
			string keep;
			cout << "Which dice would you like to keep? ";
					if (counter > 0) {
						cout << "(excluding";
			
					for (int i = 0; i < 5; i++) { 
						if (hold[i]) { 
							cout << " " << dice[i];
						} 
					}
			cout << ") ";
			}
						cin >> keep;
			for (int i = 0; i < keep.length(); i++) {
				for (int a = 0; a < 5; a++) {
					if (keep[i]-'0' == dice[a] && !hold[a]) {
						hold[a] = true;
						break;
					}
				}
			}
			if (counter > 0) {
				cout << endl;
				cout << "Which dice would you like to free? ";
				cin >> keep;
				for (int i = 0; i < keep.length(); i++) {
					for (int a = 0; a < 5; a++) {
						if (keep[i] - '0' == dice[a] && hold[a]) {
							hold[a] = false;
							break;
						}
					}
				}
			}
			counter++;
		}
	}
	cout << endl;
}

int rollOption() {
	int input;
	cout << "Would you like to " << endl;
	cout << "1. Make your pick" << endl;
	cout << "2. Roll again? " << endl;
	do {
		cin >> input;
	} while(integerCheck(input) || input < 1 || input > 2);
	cout << endl;

	return input;
}

bool checkCompatibility(int i, int* dice) {
	int counter = 0;
	if (i < 6) {
		return true;
	}
	if (i == 8) { // Three of a kind check
		for (int a = 0; a < 3; a++) {
			if (dice[a] == dice[a + 1] && dice[a] == dice[a + 2]) {
				return true;
			}
		}
	}
	if (i == 9) { // Four of a kind check
		for (int a = 0; a < 2; a++) {
			if (dice[a] == dice[a + 1] && dice[a] == dice[a + 2] && dice[a] == dice[a + 3]) {
				return true;
			}
		}
	}
	if (i == 10) { // Full house check
		bool two = false;
		bool three = false;
		int match = 0;
		for (int a = 0; a < 3; a++) {
			if (dice[a] == dice[a + 1] && dice[a] == dice[a + 2]) {
				three = true;
				match = dice[a];
				break;
			}
		}
		for (int a = 0; a < 4; a++) {
			if (dice[a] == dice[a + 1] && dice[a] != match) {
				two = true;
				break;
			}
		}
		if (three && two)
			return true;
	}
	if (i == 11) { // Small straight check
		int check[5] = {};
		int e = 0;
		for (int i = 0; i < 5; i++) {
			if (dice[i] != dice[i + 1]) {
				check[e] = dice[i];
				e++;
			}
		}
		for (int a = 0; a < 2; a++) {
			if (check[a] + 1 == check[a + 1] && check[a] + 2 == check[a + 2] && check[a] + 3 == check[a + 3]) {
				return true;
			}
		}
	}
		if (i == 12) { // Large straight check
			int a = 0;
			if (dice[a] + 1 == dice[a + 1] && dice[a] + 2 == dice[a + 2] && dice[a] + 3 == dice[a + 3] && dice[a] + 4 == dice[a + 4]) {
				return true;
			}
		}
		if (i == 13) {
			return true;
		}
		if (i == 14) {
			if (dice[0] == dice[1] && dice[0] == dice[2] && dice[0] == dice[3] && dice[0] == dice[4]) {
				return true;
			}
		}
		return false;
	}

void fillScore(int i, int* dice,int** score, bool match, int playerNumber, int players) {
	int total = 0;
	if (i >= 0 && i < 6) {
		int pips = i + 1;
		for (int a = 0; a < 5; a++) {
			if (dice[a] == pips) {
				total += pips;
			}
		}
	}
	if (i == 8) {
		if (match) {
			total = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
		}
		else total = 0;
	}
	if (i == 9) {
		if (match) {
			total = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
		}
		else total = 0;
	}
	if (i == 10) {
		if (match) {
			total = 25;
		}
		else total = 0;
	}
	if (i == 11) {
		if (match) {
			total = 30;
		}
		else total = 0;
	}
	if (i == 12) {
		if (match) {
			total = 40;
		}
		else total = 0;
	}
	if (i == 13) {
		total = dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
	}
	if (i == 14) {
		if (match) {
			total = 50;
		}
		else total = 0;
	}
	int sum = 0;
	*(*score + i*players + playerNumber) = total;
	for (int a = 0; a < 6; a++) {
		sum += *(*score + a* players + playerNumber);
	}
	*(*score + 6*players + playerNumber) = sum;
	if (sum > 62) {
	*(*score + 7*players + playerNumber) = 35;
	}
}

int totalPoints(int** score, int playerNumber, int players) {
	int sum = 0;
	for (int i = 0; i < 15; i++) {
		sum += *(*score+ i*players + playerNumber);
	}
	return sum-(*(*score + 6*players + playerNumber));
}

void printWinner(string* names,int** score, int players) {
	int mostPoints = 0;
	string winner;
	for (int i = 0; i < players; i++) {
		if (*(*score + 15*players + i) > mostPoints) {
			mostPoints = *(*score + 15 * players + i);
			winner = names[i];
		}
	}
	cout << winner << " wins!" << endl;
}

int nameCheck(string placement,int i) {
	if (placement.find("th") != string::npos && i != 8)
		i = 2;
	if (placement.find("ree of") != string::npos)
		i = 8;
	if (placement.find("fo") != string::npos &&  i!= 9)
		i = 3;
	if (placement.find("ur of") != string::npos)
		i = 9;
	return i;
}

bool integerCheck(int check) {
	bool error = true; 

	if (!check) { 
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Please input a number " << endl;
		error = true;
	}

	else {
		error = false;
	}
	return error;
}