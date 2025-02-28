#include "task1.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>

#define SIZE 5

using namespace std;

struct Student {
	string surname, group;
	int acPerformance[SIZE]; //�� academic performance - ��������
	bool excellent = false, poor = false;
};

void findExcellentStudents(Student *mas, int size) {
	for (int i = 0; i < size; ++i) {
		int count = 0;
		for (int j = 0; j < SIZE; ++j) if (mas[i].acPerformance[j] >= 10) count++;
		if (count >= 4) mas[i].excellent = true;
	}
}

void findPoorStudents(Student* mas, int size) { // poor students �� � ���� �����, � � ���� �⳺����� (��� �������� ����)
	for (int i = 0; i < size; ++i) {
		int count = 0;
		for (int j = 0; j < SIZE; ++j) if (mas[i].acPerformance[j] < 4) count++;
		if (count >= 3) mas[i].poor = true;
	}
}

void writeToFile(string fileName, Student* mas, int size) {
	fstream file(fileName, ios::app);
	if (!file) {
		cout << "���� � ������ \"" << fileName << "\" �� ��������";
		return;
	}
	for (int i = 0; i < size; ++i) {
		file << mas[i].surname << ' ' << mas[i].group << ' ';
		for (int j = 0; j < SIZE; ++j) {
			file << mas[i].acPerformance[j] << ' ';
		}
		file << (mas[i].poor ? "�⳺����" : mas[i].excellent ? "�������" : "��������") << endl;
	}
	file.close();
}

void readFromFile(string fileName) {
	fstream file(fileName, ios::in);
	if (!file) {
		cout << "���� � ������ \"" << fileName << "\" �� ��������";
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
	cout << "������ ��� ��� ��������: (������� ���� \"�������\" �������, ��� �����)\n";
	
	while (true) {
		cout << "�������: ";
		getline (cin, mas[size].surname);
		if (mas[size].surname == "") break;
		cout << "�����: ";
		getline(cin, mas[size].group);
		for (int j = 0; j < SIZE; ++j) {
			cout << j + 1 << " ������: ";
			cin >> mas[size].acPerformance[j];
		}
		cin.ignore();
		size++;
	}
		
	findExcellentStudents(mas, size);
	findPoorStudents(mas, size);
	
	int choice;
	cout << "�� ������ �� ������� ��������? 0 - �, 1 - ���\n";
	cin >> choice;

	if (choice == 1) for (int i = 0; i < size; ++i) if (mas[i].excellent) cout << mas[i].surname << " � " << mas[i].group << " � ���������" << endl;

	cout << "�� ������ �� ������� �⳺�����? 0 - �, 1 - ���\n";
	cin >> choice;

	if (choice == 1) for (int i = 0; i < size; ++i)	if (mas[i].poor) cout << mas[i].surname << " � " << mas[i].group << " � �⳺������" << endl;
	
	cout << "�� ������ �� ������� ����� ������? 0 - �, 1 - ���\n";
	cin >> choice;
	if (choice == 1) readFromFile("task1.txt");
	writeToFile("task1.txt", mas, size);
	delete[] mas;
	welcoming();
}