#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;

string wuzPoppin();

int main() {
	string pop = "What's poppin?";
	cout << pop << endl;
	cout << wuzPoppin();

	return 0;
}

string wuzPoppin() {
	string whip = "Brand new whip just hopped in";
	return whip;
}