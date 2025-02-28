#include "task1.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>

#define SIZE 5

using namespace std;

struct Student {
	string surname, group;
	int acPerformance[SIZE]; //від academic performance - успішність
	bool excellent = false, poor = false;
};

void findExcellentStudents(Student *mas, int size) {
	for (int i = 0; i < size; ++i) {
		int count = 0;
		for (int j = 0; j < SIZE; ++j) if (mas[i].acPerformance[j] >= 10) count++;
		if (count >= 4) mas[i].excellent = true;
	}
}

void findPoorStudents(Student* mas, int size) { // poor students не в сенсі бідних, а в сенсі двієчників (так переклав гугл)
	for (int i = 0; i < size; ++i) {
		int count = 0;
		for (int j = 0; j < SIZE; ++j) if (mas[i].acPerformance[j] < 4) count++;
		if (count >= 3) mas[i].poor = true;
	}
}

void writeToFile(string fileName, Student* mas, int size) {
	fstream file(fileName, ios::app);
	if (!file) {
		cout << "Файл з назвою \"" << fileName << "\" не знайдено";
		return;
	}
	for (int i = 0; i < size; ++i) {
		file << mas[i].surname << ' ' << mas[i].group << ' ';
		for (int j = 0; j < SIZE; ++j) {
			file << mas[i].acPerformance[j] << ' ';
		}
		file << (mas[i].poor ? "двієчник" : mas[i].excellent ? "відмінник" : "хорошист") << endl;
	}
	file.close();
}

void readFromFile(string fileName) {
	fstream file(fileName, ios::in);
	if (!file) {
		cout << "Файл з назвою \"" << fileName << "\" не знайдено";
		return;
	}
	string line;
	while (getline(file, line)) cout << line;
	file.close();
}

void task1()
{
	Student* mas = new Student[100];
	int size = 0;
	cin.ignore();
	cout << "Вводіть дані про студентів: (залиште поле \"Прізвище\" порожнім, щоб вийти)\n";
	
	while (true) {
		cout << "Прізвище: ";
		getline (cin, mas[size].surname);
		if (mas[size].surname == "") break;
		cout << "Група: ";
		getline(cin, mas[size].group);
		for (int j = 0; j < SIZE; ++j) {
			cout << j + 1 << " оцінка: ";
			cin >> mas[size].acPerformance[j];
		}
		cin.ignore();
		size++;
	}
		
	findExcellentStudents(mas, size);
	findPoorStudents(mas, size);
	
	int choice;
	cout << "Чи хочете ви вивести відмінників? 0 - ні, 1 - так\n";
	cin >> choice;

	if (choice == 1) for (int i = 0; i < size; ++i) if (mas[i].excellent) cout << mas[i].surname << " з " << mas[i].group << " є відмінником" << endl;

	cout << "Чи хочете ви вивести двієчників? 0 - ні, 1 - так\n";
	cin >> choice;

	if (choice == 1) for (int i = 0; i < size; ++i)	if (mas[i].poor) cout << mas[i].surname << " з " << mas[i].group << " є двієчником" << endl;
	
	cout << "Чи хочете ви вивести минулі записи? 0 - ні, 1 - так\n";
	cin >> choice;
	if (choice == 1) readFromFile("task1.txt");
	writeToFile("task1.txt", mas, size);
	delete[] mas;
	welcoming();
}