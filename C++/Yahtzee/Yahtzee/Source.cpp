#include <iostream>
#include <time.h>
#include <conio.h>
#include <string>

using namespace std;

void welcome();
int playerCount();
int rollOption();
string playerNames();
void printChart(string[], string[],int[16][4], int);
void rollDice(int[16][4], string[], int, string*, bool[16][4]);
bool checkCompatibility(int, int*);
void fillScore(int, int*, int[16][4], bool, int);
int totalPoints(int[16][4], int);
void printWinner(string[], int[16][4], int);
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
	string names[4];
	int score[16][4] = {0};
	bool used[16][4] = { false };
	int players = playerCount();
	int roundCount = 13 * players;
	int playerNumber = 0;
	for (int i = 0; i < players; i++) {
		names[i] = playerNames();
	}
	for (int i = 0; i < roundCount; i++) {
		if (playerNumber == players) {
			playerNumber = 0;
		}
		printChart(names, rows, score, players);
		rollDice(score, rows, playerNumber, names, used);
		playerNumber++;
	}
	printChart(names, rows, score, players);
	printWinner(names, score, players);

	return 0;
}

void welcome() {
	cout << "Welcome to C++ yahtzee. " << endl;
}

int playerCount() {
	int players = 0;
	string input = "n";
	bool yesno = false;
	while (input == "n") {
		while (players > 4 || players < 1) {
			cout << "How many players?" << endl;
			do {
				cin >> players;
			} while (integerCheck(players));
			if (players > 4 || players < 1) {
				cout << "Please pick between 1-4" << endl;
			}
		}
		while (!yesno) {
			cout << "You have selected " << players << " players. Are you sure? (y/n) ";
				cin >> input;
			if (input == "y" || input == "n")
				yesno = true;
		}
	}
	return players;
}

string playerNames() {
	string name;
	cout << "Input player name: ";
	cin >> name;

	return name;
}


void printChart(string* names, string* rows,int score[16][4], int players) {
	cout << "\t \t";
	for (int i = 0; i < players; i++) {
		cout << names[i] << "\t";
	}
	cout << endl;
	if (players == 4) {
		for (int i = 0; i < 16; i++) {
			if (i == 0 || i == 6 || i == 8 || i == 15) {
				cout << "--------------------------------------------" << endl;
			}
			if (i < 8 || (i > 12 && i != 15))
				cout << rows[i] << "\t \t" << score[i][0] << " \t" << score[i][1] << "\t" << score[i][2] << "\t" << score[i][3] << endl;
			else
				cout << rows[i] << "\t" << score[i][0] << " \t" << score[i][1] << "\t" << score[i][2] << "\t" << score[i][3] << endl;
		}
	}
	if (players == 3) {
		for (int i = 0; i < 16; i++) {
			if (i == 0 || i == 6 || i == 8 || i == 15) {
				cout << "------------------------------------" << endl;
			}
			if (i < 8 || (i > 12 && i != 15))
				cout << rows[i] << "\t \t" << score[i][0] << " \t" << score[i][1] << "\t" << score[i][2] << endl;
			else
				cout << rows[i] << "\t" << score[i][0] << " \t" << score[i][1] << "\t" << score[i][2] << endl;
		}
	}
	if (players == 2) {
		for (int i = 0; i < 16; i++) {
			if (i == 0 || i == 6 || i == 8 || i == 15) {
				cout << "----------------------------" << endl;
			}
			if (i < 8 || (i > 12 && i != 15))
				cout << rows[i] << "\t \t" << score[i][0] << " \t" << score[i][1] << endl;
			else
				cout << rows[i] << "\t" << score[i][0] << " \t" << score[i][1] << endl;
		}
	}
	if (players == 1) {
		for (int i = 0; i < 16; i++) {
			if (i == 0 || i == 6 || i == 8 || i == 15) {
				cout << "--------------------" << endl;
			}
			if (i < 8 || (i > 12 && i != 15))
				cout << rows[i] << "\t \t" << score[i][0] << endl;
			else
				cout << rows[i] << "\t" << score[i][0] << endl;
		}
	}
	cout << endl;
}

void rollDice(int score[16][4], string* rows, int playerNumber, string* names, bool used[16][4]) {
	int option;
	int dice[5] = {4,3,6,5,2};
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
			for (int i = 0; i < 5; i++)
			{
				for (int j = i + 1; j < 5; j++)
				{
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
							if (!used[i][playerNumber]) {
								match = checkCompatibility(i, dice);
								fillScore(i, dice, score, match, playerNumber);
								score[15][playerNumber] = totalPoints(score, playerNumber);
								used[i][playerNumber] = true;
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
				cout << "Which dice would you like to free?" << endl;
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
	}while(integerCheck(input));
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
		for (int a = 0; a < 3; a++) {
			if (dice[a] + 1 == dice[a + 1] && dice[a] + 2 == dice[a + 2] && dice[a] + 3 == dice[a + 3]) {
				return true;
			}
		}
	}
	if (i == 12) { // Large straight check
		for (int a = 0; a < 2; a++) {
			if (dice[a] + 1 == dice[a + 1] && dice[a] + 2 == dice[a + 2] && dice[a] + 3 == dice[a + 3] && dice[a] + 4 == dice[a + 4]) {
				return true;
			}
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

void fillScore(int i, int* dice,int score[16][4], bool match, int playerNumber) {
	int total = 0;
	if (i == 0) {
		for (int a = 0; a < 5; a++) {
			if (dice[a] == 1) {
				total++;
			}
		}
	}
	if (i == 1) {
		for (int a = 0; a < 5; a++) {
			if (dice[a] == 2) {
				total += 2;
			}
		}
	}
	if (i == 2) {
		for (int a = 0; a < 5; a++) {
			if (dice[a] == 3) {
				total += 3;
			}
		}
	}
	if (i == 3) {
		for (int a = 0; a < 5; a++) {
			if (dice[a] == 4) {
				total += 4;
			}
		}
	}
	if (i == 4) {
		for (int a = 0; a < 5; a++) {
			if (dice[a] == 5) {
				total += 5;
			}
		}
	}
	if (i == 5) {
		for (int a = 0; a < 5; a++) {
			if (dice[a] == 6) {
				total += 6;
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
	score[i][playerNumber] = total;
	for (int a = 0; a < 6; a++) {
		sum += score[a][playerNumber];
	}
	score[6][playerNumber] = sum;
	if (sum > 62) {
		score[7][playerNumber] = 35;
	}
}

int totalPoints(int score[16][4], int playerNumber) {
	int sum = 0;
	for (int i = 0; i < 15; i++) {
		sum += score[i][playerNumber];
	}
	return sum-score[6][playerNumber];
}

void printWinner(string names[],int score[16][4], int players) {
	int mostPoints = 0;
	string winner;
	for (int i = 0; i < players; i++) {
		if (score[15][i] > mostPoints) {
			mostPoints = score[15][i];
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

