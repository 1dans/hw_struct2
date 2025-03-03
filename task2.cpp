#include "task2.h"
#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
	int year, month, day;
} Year;

typedef struct {
	string surname, name;
	int age;
	Year dateOfBirth;
} Man;

vector<Man> readFromFile(vector<Man> people) {
	Man person;
	fstream file("task2.txt", ios::in);
	if (!file) {
		cout << "���� \"task2.txt\" �� ��������";
		return people;
	}
	while (file >> person.surname >> person.name >> person.age >> person.dateOfBirth.year >> person.dateOfBirth.month >> person.dateOfBirth.day) people.push_back(person);
	file.close();
	return people;
}

void writeToFile(vector<Man> people) {
	fstream file("task2.txt", ios::out);
	if (!file) {
		cout << "���� \"task2.txt\" �� ��������";
		return;
	}
	for (int i = 0; i < people.size(); ++i) file << people[i].surname << ' ' << people[i].name << ' ' << people[i].age << ' ' << people[i].dateOfBirth.year << ' ' << people[i].dateOfBirth.month << ' ' << people[i].dateOfBirth.day << endl;
	file.close();
	cout << "��� �������� � ����\n";
}

vector<Man> sortArray(vector<Man> people, int size, string parameter) {
	cout << "� ����� ������� �� ������ ����������� ���?\n1 - ��������� (�-�)\n2 - �������� (�-�)\n��� ����: ";
	int order;
	cin >> order;
	if (parameter == "surname") sort(people.begin(), people.end(), [](const Man& person1, const Man& person2) -> bool {return person1.surname < person2.surname; });
	else sort(people.begin(), people.end(), [](const Man& person1, const Man& person2) -> bool {return person1.name < person2.name; });
	if (order == 2) reverse(people.begin(), people.end());
	return people;
}

void showArray(vector<Man> people) {
	for (auto i : people) cout << i.surname << ' ' << i.name << " - " << i.age << " ����, ���������(����) " << i.dateOfBirth.year << '.' << i.dateOfBirth.month << '.' << i.dateOfBirth.day << endl;
}

vector<Man> addPerson(vector<Man> people) {
	string surname="---", name;
	int age;
	Year dateOfBirth;
	while (surname!="") {
		cin.ignore();
		cout << "�������: ";
		getline(cin, surname);
		if (surname == "") break;
		cout << "��'�: ";
		getline(cin, name);
		cout << "³�: ";
		cin >> age;
		cout << "���� ���������� (����� �����, � ������: �� ����� ����): ";
		cin >> dateOfBirth.year >> dateOfBirth.month >> dateOfBirth.day;
		Man man = { surname, name, age, dateOfBirth.year, dateOfBirth.month, dateOfBirth.day };
		people.push_back(man);
	}
	return people;
}

int searchPerson(vector<Man> people, int size, string searchedSurname, string searchedName) {
	vector<int> searchedPeopleIndexes; // �� �������, ���� ���������� ����� 1 ������ � ������� ������ �� �������� 
	for (int i = 0; i < size; ++i) if (people[i].surname == searchedSurname && people[i].name == searchedName) searchedPeopleIndexes.push_back(i);

	if (searchedPeopleIndexes.size() == 0) {
		cout << "����� ������ � ����� ��'�� �� �������� �� ���� ��������\n";
		return -1;
	}
	else if (searchedPeopleIndexes.size() == 1) return searchedPeopleIndexes[0];
	else {
		cout << "���� �������� ����� ���� ������: \n";
		for (auto i : searchedPeopleIndexes) cout << people[i].surname << ' ' << people[i].name << " - " << people[i].age << " ����, ���������(����) " << people[i].dateOfBirth.year << '.' << people[i].dateOfBirth.month << '.' << people[i].dateOfBirth.day << endl;
		cout << "��� � ��� ��� �������? ";
		int choice;
		cin >> choice;
		choice--;
		return searchedPeopleIndexes[choice];
	}
}

vector<Man> deletePerson(vector<Man> people, int size) {
	string surname, name;
	cin.ignore();
	cout << "������ ������� ������, ��� ������ ��������: ";
	getline(cin, surname);
	cout << "������ ��'� ������, ��� ������ ��������: ";
	getline(cin, name);
	int personToDelete = searchPerson(people, size, surname, name);
	people.erase(people.begin() + personToDelete);
	return people;
}

void showByBirthday(vector<Man> people) {
	vector<Man> birthdayPeople; //����������, � ��������� ���� ������������ ����� ��� �����
	cout << "������ ����� ��������� �����: ";
	int month;
	cin >> month;
	for (auto i : people) if (i.dateOfBirth.month == month) birthdayPeople.push_back(i);
	cout << "���������� �����: \n";
	showArray(birthdayPeople);
}

vector<Man> editPerson(vector<Man> people) {
	int characteristic = -1, index = 0, age, year, month, day;
	string person, surname, name;
	showArray(people);
	cin.ignore();
	cout << "����� ��� ��� ������ �� ����� �� ����������? \n������ ����� �� ��'�\n";
	getline(cin, person);
	index = person.find(" ");
	surname = person.substr(0, index);
	name = person.substr(index + 1);
	index = searchPerson(people, people.size(), surname, name);
	while (characteristic!=0) {
		cout << "��� �������������� �� ����� �� ����������?\n1 - �������\n2 - ��'�\n3 - ³�\n4 - ���� ����������\n0 - �������� �����������\n";
		cin >> characteristic;
		switch (characteristic) {
		case 1:
			cin.ignore();
			cout << "������ ���� �������: ";
			getline(cin, surname);
			people[index].surname = surname;
			break;
		case 2:
			cin.ignore();
			cout << "������ ���� ��'�: ";
			getline(cin, name);
			people[index].name = name;
			break;
		case 3:
			cout << "������ ����� ��: ";
			cin >> age;
			people[index].age = age;
			break;
		case 4:
			cout << "������ ���� ���� ����������(� ������ �� �� ��): ";
			cin >> year >> month >> day;
			people[index].dateOfBirth.year = year;
			people[index].dateOfBirth.month = month;
			people[index].dateOfBirth.day = day;
			break;
		case 0: break;
		}
	}
	return people;
}

void task2()
{
	vector<Man> people;
	people = readFromFile(people);
	int choice = -1, index = 0;
	string surname, name;
	cin.ignore();
	while (choice != 0) {
		cout << "������, �� ������ �������:\n1 - ������ ��� ��� �����\n2 - �������� ��� ��� ������\n3 - ���������� �� ��������\n4 - ���������� �� ��'��\n5 - ��������� ������ �����\n6 - ������� ���������� �����\n7 - ����� �� �������� �� ��'��\n8 - ����������� ������\n9 - �������� ��� � ����\n0 - ��������� ������ � �������� ����\n";
		cin >> choice;
		switch (choice) {
		case 1: people = addPerson(people); break;
		case 2: people = deletePerson(people, people.size()); break;
		case 3: people = sortArray(people, people.size(), "surname"); break;
		case 4: people = sortArray(people, people.size(), "name"); break;
		case 5:
			cout << "��� �� ���: \n";
			showArray(people);
			break;
		case 6: showByBirthday(people); break;
		case 7:
			cin.ignore();
			cout << "������ ������� ������, ��� ������ ������: ";
			getline(cin, surname);
			cout << "������ ��'� ������, ��� ������ ������: ";
			getline(cin, name);
			index = searchPerson(people, people.size(), surname, name);
			cout << people[index].surname << ' ' << people[index].name << " - " << people[index].age << " ����, ���������(����) " << people[index].dateOfBirth.year << '.' << people[index].dateOfBirth.month << '.' << people[index].dateOfBirth.day << endl;
			break;
		case 8: people = editPerson(people); break;
		case 9: writeToFile(people);
		case 0: break;
		default: cout << "������ ������� ����\n"; break;
		}
	}
	writeToFile(people);
	cout << "������ ���������! ����� ��� �������� � ����\n";
	welcoming();
}
