#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <time.h>

//DO ADD RAND/FINISH COLLISION/DO DELETE


using namespace std;

struct student {
    char firstName[20];
    char lastName[20];
    float gpa;
    int id;
    student* next; //sets next so we can go to next studnet in the linked list
};

void add(student* newStudent, student** hashtable, int &size);
void print(student** hashtable, int size);


int main() { 

	bool play = true;
	int id;
	student** hashtable = new student * [100]; // creates hashtable
	int size = 100;
	
	while (play == true) {
		
		id = rand() % 999999 + 1; //generates random ID value

		//Gets add or delete or print or quit 
		char str[10]; 
		cout << "Input: ADD, DELETE, PRINT, or QUIT: "; 
		cin.get(str, 10);
		cin.get();

		//Checks if add or delete or print or quit
		if (strcmp(str, "ADD") == 0) {
			student* newStudent = new student();
			newStudent -> next = NULL;
			cout << "Please enter students first name: ";
			cin >> newStudent -> firstName;
			cin.get();
			cout << "Please enter students last name: ";
			cin >> newStudent -> lastName;
			cin.get();
			cout << "Please enter your student ID: ";
			cin >> newStudent -> id;
			cin.get();
			cout << "Please enter your GPA: ";
			cin >> newStudent -> gpa;
			cin.get();
			add(newStudent, hashtable, size);
		}
		else if (strcmp(str, "DELETE") == 0) {
			cout << "del(storage);" << endl;
		}
		else if (strcmp(str, "PRINT") == 0) {	
			print(hashtable, size);
		}
		else if (strcmp(str, "QUIT") == 0) {
			play = false;	
		}
		else {
			cout << "Invalid Input" << endl;
		}
	}
}

void add(student* newStudent, student** hashtable, int &size) {
	//algorithm 
	int index = (newStudent -> id) % size;
	int tracker = 0;

	//no collision
	if (hashtable[index] == NULL) {
		hashtable[index] = newStudent;
	}	

	else {
		//first collision
		if ((hashtable[index]) -> next == NULL) {
			(hashtable[index]) -> next = newStudent;
			tracker += 1;
		}
		//second collision
		else if (((hashtable[index]) -> next) -> next == NULL) {
			((hashtable[index]) -> next) -> next = newStudent;
			tracker += 1;
		}
		//third collision
		else if ((((hashtable[index]) -> next) -> next) -> next == NULL) {
			(((hashtable[index]) -> next) -> next) -> next = newStudent;
			tracker += 1;
		}
		//on fourth collision
		else {
			student** temp = new student * [size];	
			for (int i = 0; i < size; i++) {
				temp[i] = hashtable[i];
			}
			size = size * 2;
			hashtable = new student * [size];
			for (int i = 0; i < size; i++) {
				hashtable[i] = NULL;
			}
			for (int i = 0; i < size; i++) {
				if (temp[i] != NULL) {
					if (temp[i] -> next != NULL) {
					}
				}
			}
		}
	}
}

void print(student** hashtable, int size) {
	for (int i = 0; i < size; i++) {
		if (hashtable[i] != NULL) {
			cout << "First Name: " << hashtable[i] -> firstName << endl;
			cout << "Last Name: " << hashtable[i] -> lastName << endl;
			cout << "ID: " << hashtable[i] -> id << endl;
			cout << "GPA: " << hashtable[i] -> gpa << endl;
			student* next = hashtable[i]->next;
			if (next != NULL) {
				cout << "First Name: " << next -> firstName << endl;
				cout << "Last Name: " << next -> lastName << endl;
				cout << "ID: " << next -> id << endl;
				cout << "GPA: " << next -> gpa << endl;
			}
		}

	}
}
