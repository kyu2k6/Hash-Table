// Kevin Yu
//2/27/23
//Add student print delete student

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <time.h>

using namespace std;

struct student {
    char firstName[20];
    char lastName[20];
    float gpa;
    int id;
    student* next; //sets next so we can go to next studnet in the linked list
};

void add(student* newStudent, student** hashtable, int size);
void print(student** hashtable, int size);
void del(student** hashtable, int id, int size);
bool collision(student** hashtable, int size);


int main() {

        bool play = true;
        int id;
        srand(time(NULL));
        id = rand() % 999999 + 1; // make random id
        student** hashtable = new student * [100]; // creates hashtable
        int size = 100;


        while (play == true) {

                //Gets add or delete or print or quit
                char str[10];
                cout << "Input: ADD, DELETE, PRINT, or QUIT, ADDRAND: ";
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
                        if (collision(hashtable, size)) {
                                student** temp = new student * [size];
                                for (int i = 0; i < size; i++) {
                                        temp[i] = hashtable[i];
                                }
                                int newSize = 2* size;
                                hashtable = new student * [newSize];
                                for (int x = 0; x < newSize; x++) {
                                        hashtable[x] = NULL;
                                }
                                for (int y = 0; y < size; y++) {
                                                if(temp[y] != NULL) {
                                                student* move = temp[y];
                                                if (move -> next != NULL) {
                                                        student* newNext = move -> next;
                                                        move -> next = NULL;
                                                        add(newNext, hashtable, newSize);
                                                        if (newNext -> next != NULL) {
                                                                student* newNext2 = newNext -> next;
                                                                newNext -> next = NULL;
                                                                add(newNext2, hashtable, newSize);
                                                        }
                                                }
                                                add(move, hashtable, newSize);
                                        }
                                }
                                delete[] temp;
                                size = newSize;
                        }
                }
                else if (strcmp(str, "ADDRAND") == 0) {
                        int count;
                        char** firstname = new char* [20];
                        char **lastname = new char* [20];
                        for (int i = 0; i < 20; i++) {
                                firstname[i] = new char[81];
                                lastname[i] = new char[81];
                        }
                        cout << endl << "Number of students to add? ";
                        cin >> count;
                        cin.get();
                        ifstream myfile1("first.txt");
                        int line = 0;
                        char first[81];
                        while (line < 20) {
                                myfile1.getline(first, 81);
                                strcpy(firstname[line], first);
                                line++;
                        }
                        ifstream myfile2("last.txt");
                        char last[81];
                        line = 0;
                        while (line < 20) {
                                myfile2.getline(last, 81);
                                strcpy(lastname[line], last);
                                line++;
                        }
                        while (count > 0) {
                                student* newStudent = new student();

                                //make random numbers between 0 and 19
                                int randfirst = rand() % 19;
                                int randlast = rand() % 19;

                                //assign random data to new student
                                strcpy(newStudent->firstName, firstname[randfirst]);
                                strcpy(newStudent->lastName, lastname[randlast]);
                                newStudent->id = id;
                                newStudent->gpa = (float)rand() / (RAND_MAX) * 5;
                                id = id + 100;

                                add(newStudent, hashtable, size);

                                if (collision(hashtable, size)) {
                                        student** temp = new student * [size];
                                        for (int i = 0; i < size; i++) {
                                                temp[i] = hashtable[i];
					}
					int newSize = 2 * size;
					hashtable = new student * [newSize];
                                        for (int x = 0; x < newSize; x++) {
                                                hashtable[x] = NULL;
                                        }
                                        for (int y = 0; y < size; y++) {
                                                if(temp[y] != NULL) {
                                                        student* move = temp[y];
                                                        if (move -> next != NULL) {
                                                                student* newNext = move -> next;
                                                                move -> next = NULL;
                                                                add(newNext, hashtable, newSize);
                                                                if (newNext -> next != NULL) {
                                                                        student* newNext2 = newNext -> next;
                                                                        newNext -> next = NULL;
                                                                        add(newNext2, hashtable, newSize);
                                                                }
                                                        }
                                                        add(move, hashtable, newSize);
                                                }
                                        }
                                        delete[] temp;
                                        size = newSize;
                                }
                                count--;
                        }
                }
                else if (strcmp(str, "DELETE") == 0) {
                        cout << "What is ID of deleted student? ";
                        int delid;
                        cin >> delid;
                        cin.get();
                        del(hashtable, delid, size);
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

void add(student* newStudent, student** hashtable, int size) {
        //algorithm
        int index = (newStudent -> id) % size;

        //no collision
        if (hashtable[index] == NULL) {
                hashtable[index] = newStudent;
        }

        else {
                //first collision
                if ((hashtable[index]) -> next == NULL) {
                        (hashtable[index]) -> next = newStudent;
                }
                //more colliisons
                else {
                        ((hashtable[index]) -> next) -> next = newStudent;
                }
	}
}
void print(student** hashtable, int size) {
        for (int i = 0; i < size; i++) {
                if (hashtable[i] != NULL) {
                        cout << "First Name: " << hashtable[i] -> firstName << endl;
                        cout << "Last Name: " << hashtable[i] -> lastName << endl;
                        cout << "ID: " << hashtable[i] -> id << endl;
                        cout << "GPA: " << setprecision(3) << hashtable[i] -> gpa << endl;
                        student* next = hashtable[i]->next;
                        if (next != NULL) {
                                cout << "First Name: " << next -> firstName << endl;
                                cout << "Last Name: " << next -> lastName << endl;
                                cout << "ID: " << next -> id << endl;
                                cout << "GPA: " << setprecision(3) << next -> gpa << endl;
                                student* next2 = next -> next;
                                if (next2 != NULL) {
                                        cout << "First Name: " << next2 -> firstName << endl;
                                        cout << "Last Name: " << next2 -> lastName << endl;
                                        cout << "ID: " << next2 -> id << endl;
                                        cout << "GPA: " << fixed << setprecision(3) << next2 -> gpa << endl;
                                        student* next3 = next2 -> next;
                                        if (next3 != NULL) {
                                                cout << "First Name: " << next3 -> firstName << endl;
                                                cout << "Last Name: " << next3 -> lastName << endl;
                                                cout << "ID: " << next3 -> id << endl;
                                                cout << "GPA: " << fixed << setprecision(3) << next3 -> gpa << endl;
                                        }
                                }

                        }
                }

        }
}

void del(student** hashtable, int id, int size) {
        int index = id % size;
        if (hashtable[index] == NULL) {
                cout << endl << "No one here" << endl;
        }

        else {
                //same id
                if (hashtable[index] -> id == id) {
                        if (hashtable[index] -> next == NULL) {
                                hashtable[index] = NULL;
                        }
                        else {
                                //move them
                                student* newhead = hashtable[index] -> next;
                                hashtable[index] = newhead;
                        }
                }
                else {
                        if (hashtable[index] -> next == NULL) {
                                cout << "No one here" << endl;
                        }
                        else {
                                if (hashtable[index] -> next -> id == id) {
                                        hashtable[index] -> next = NULL;
                                }
                                else {
                                        cout << "No one here" << endl;
                                }
                        }
                }
        }
}
bool collision(student** hashtable, int size) {
	bool rehash = false;
	int CC = 0;
	while (rehash == false && CC < size) {
		if (hashtable[CC] != NULL) {
			if ((hashtable[CC] -> next != NULL) {
				if (((hashtable[CC]) -> next) -> next != NULL) {
					rehash = true;
				}
			}
		}
		CC++;
	}
	return rehash;
}
                                                                                                                                                                             208,48-69     91%


