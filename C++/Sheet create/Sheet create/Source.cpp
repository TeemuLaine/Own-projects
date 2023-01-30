#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string inputFunction(string);
bool check(int);

int main() {
	string name, age, country;
	int count = 0;
	ofstream outfile("sheet.csv");
	cout << "How many people would you like to input? " << endl;
	do {
		cin >> count;
		cin.ignore(10, '\n');
	} while (check(count));
	outfile << "Name;Age;Country" << endl;
	for (int i = 0; i < count; i++) {
		outfile << inputFunction("name") << ";";
		outfile << inputFunction("age") << ";";
		outfile << inputFunction("country") << endl;
	}
	outfile.close();


	return 0;
}

string inputFunction(string s) {
	string input;
	cout << "Input the person's " << s << endl;
	getline(cin, input);
	return input;
}

bool check(int i) {
	bool fail = true;

	if (!i) {
		cin.clear();
		cin.ignore(80, '\n');
		cout << "Not a number, try again." << endl;
		fail = true;
	}

	else {
		fail = false;
	}
	return fail;
}
