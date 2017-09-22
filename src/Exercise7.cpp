#include "OptChars.h"
#include "OptWord.h"
#include <iostream>
#include "Options.h"
using namespace std;
OptChars opt;
OptWord opt2;

int main(int argc, char** argv) {
try {
	string validOpt = "abo";
	//number of valid options.
	int WordArgs;
	int i = 2;
	string validWords[i];
	validWords[0] = "log";
	validWords[1] = "help";

	//copy dynamically allocated obj to the global class and clean up
	OptChars *obj;
	obj = new OptChars(argc, (const char**) argv);
	opt = *obj;
	delete obj;
	obj = NULL;

	//copy dynamically allocated obj to the global class and clean up
	OptWord *obj2;
	obj2 = new OptWord(argc, (const char**) argv);
	opt2 = *obj2;
	delete obj2;
	obj2 = NULL;

	//sets the valid options for '-' commands, count them up and loop them out
	opt.setOptstring(validOpt);
	int args = opt.numopt();
	if (args != 0) {
		cout << "Valid chars on cmdline: " << args << endl;
		for (int o = 1; o <= args; o++) {
			string str = opt.getopt();
			if (str != "INVALID")			//don't want to spam "INVALID"
			{
				cout << "Found match: -" << str << endl;
			} else {
				throw "No CHAR options entered!";
			}
		}

	}

	//sets the valid options for '--' commands and count them up
	for (int j = 0; j < i; j++) {
		opt2.setOptstring(validWords[j]);
		args = opt2.numopt();
		WordArgs += args;
	}
	if (WordArgs != 0) {
		cout << "valid words on cmdline: " << WordArgs << endl;

		//loop out the '--' commands. Nested for loop because words options
		// take a string each and needs to be set each time
		for (int j = 0; j < i; j++) {
			opt2.setOptstring(validWords[j]);
			for (int o = 1; o <= WordArgs; o++) {
				string str = opt2.getopt();
				if (str != "INVALID")		//don't want to spam "INVALID"
				{
					cout << "Found match: -" << str << endl;
				} else {
					throw "No WORD options entered!";
				}
			}
		}
	}
}
catch (int x) {
	cout << "ErrorID: " << x << endl;
}
catch (string &s) {
	cout << s << endl;
}
catch (...) {
	cout << "something went wrong" << endl;
}
return 0;
}
