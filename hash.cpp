#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct student {
    char firstName[20];
    char lastName[20];
    float gpa;
    int id;
    student* next;
};

void add();

int main() {
	
	bool play = true;
	int id;
	id = rand() % 999999 + 1; //generate random ID
	student** hashtable = new student * [100]; // creates hashtable
	int size = 100;

	while (play == true) {
		cout << id;
		//Gets add or delete or print or quit 
		char str[10]; 
		cout << "Input: ADD, DELETE, PRINT, or QUIT: "; 
		cin.get(str, 10);
		cin.get();

		//Checks if add or delete or print or quit
		if (strcmp(str, "ADD") == 0) {
			cout << "add(storage);" << endl;
		}
		else if (strcmp(str, "DELETE") == 0) {
			cout << "del(storage);" << endl;
		}
		else if (strcmp(str, "PRINT") == 0) {	
			cout << "print(storage);" << endl;
		}
		else if (strcmp(str, "QUIT") == 0) {
			play = false;	
		}
		else {
			cout << "Invalid Input" << endl;
		}
	}
}

void add() {
	
}


