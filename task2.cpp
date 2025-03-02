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

vector<Man> sortArray(vector<Man> people, int size, string parameter) {
	cout << "В якому порядку ви хочете відсортувати дані?\n1 - зростання (А-Я)\n2 - спадання (Я-А)\nВаш вибір: ";
	int order;
	cin >> order;
	if (parameter == "surname") sort(people.begin(), people.end(), [](const Man& person1, const Man& person2) -> bool {return person1.surname < person2.surname; });
	else sort(people.begin(), people.end(), [](const Man& person1, const Man& person2) -> bool {return person1.name < person2.name; });
	if (order == 2) reverse(people.begin(), people.end());
	return people;
}

void showArray(vector<Man> people) {
	cout << "Ось усі збережені дані\n";
	for (auto i : people) cout << i.surname << ' ' << i.name << " - " << i.age << "років, народився(лась) " << i.dateOfBirth.year << '.' << i.dateOfBirth.month << '.' << i.dateOfBirth.day << endl;
}

Man addPerson() {
	string surname, name;
	int age;
	Year dateOfBirth;
	cout << "Прізвище: ";
	getline(cin, surname);
	if (surname == "") return { "" };
	cout << "Ім'я: ";
	getline(cin, name);
	cout << "Вік: ";
	cin >> age;
	cout << "Дата народження (через пробіл, в форматі: рік місяць день): ";
	cin >> dateOfBirth.year >> dateOfBirth.month >> dateOfBirth.day;
	Man man = { surname, name, age, dateOfBirth.year, dateOfBirth.month, dateOfBirth.day };
	return man;
}

int searchPerson(vector<Man> people, int size, string searchedSurname, string searchedName) {
	vector<int> searchedPeopleIndexes; // на випадок, якщо знайдеться більше 1 людини з шукаємим іменем та прізвищем 
	for (int i = 0; i < size; ++i) if (people[i].surname == searchedSurname && people[i].name == searchedName) searchedPeopleIndexes.push_back(i);

	if (searchedPeopleIndexes.size() == 0) {
		cout << "Жодної людини з таким ім'ям та прізвищем не було знайдено\n";
		return -1;
	}
	else if (searchedPeopleIndexes.size() == 1) return searchedPeopleIndexes[0];
	else {
		cout << "Було знайдено більше однієї людини: \n";
		for (auto i : searchedPeopleIndexes) cout << people[i].surname << ' ' << people[i].name << " - " << people[i].age << "років, народився(лась) " << people[i].dateOfBirth.year << '.' << people[i].dateOfBirth.month << '.' << people[i].dateOfBirth.day << endl;
		cout << "Хто з них вам потрібен? ";
		int choice;
		cin >> choice;
		choice--;
		return searchedPeopleIndexes[choice];
	}
}

vector<Man> deletePerson(vector<Man> people, int size) {
	string surname, name;
	cout << "Введіть прізвище людини, яку хочете видалити: ";
	getline(cin, surname);
	cout << "Введіть ім'я людини, яку хочете видалити: ";
	getline(cin, name);
	int personToDelete = searchPerson(people, size, surname, name);
	people.erase(people.begin() + personToDelete);
	return people;
}



void task2()
{
	vector<Man> people;
	cin.ignore();
	cout << "Оберіть, що хочете зробити:\n1 - Додати дані про людей\n2 - Видалити дані про людину\n3 - Сортування за прізвищем\n4 - Сортування за ім'ям\n5 - Виведення списку людей\n6 - Вивести іменинників місяця\n7 - Пошук за прізвищем та ім'ям\n8 - Редагування запису\n0 - Завершити роботу";
	int choice;
	string surname, name;
	cin >> choice;
	switch (choice) {
	case 1:
		while (true) {
			Man man = addPerson();
			if (man.surname == "") break;
			people.push_back(man);
		}
		break;
	case 2: deletePerson(people, people.size()); break;
	case 3: sortArray(people, people.size(), "surname"); break;
	case 4: sortArray(people, people.size(), "name"); break;
	case 5: break;
	case 6: break;
	case 7: 
		cout << "Введіть прізвище людини, яку хочете видалити: ";
		getline(cin, surname);
		cout << "Введіть ім'я людини, яку хочете видалити: ";
		getline(cin, name);
		searchPerson(people, people.size(), surname, name);
		break;
	case 8: break;
	case 0: break;
	default: cout << "Такого варіанту немає"; break;
	}
	cout << "Роботу завершено!";

}
