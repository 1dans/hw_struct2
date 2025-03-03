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
		cout << "Файл \"task2.txt\" не знайдено";
		return people;
	}
	while (file >> person.surname >> person.name >> person.age >> person.dateOfBirth.year >> person.dateOfBirth.month >> person.dateOfBirth.day) people.push_back(person);
	file.close();
	return people;
}

void writeToFile(vector<Man> people) {
	fstream file("task2.txt", ios::out);
	if (!file) {
		cout << "Файл \"task2.txt\" не знайдено";
		return;
	}
	for (int i = 0; i < people.size(); ++i) file << people[i].surname << ' ' << people[i].name << ' ' << people[i].age << ' ' << people[i].dateOfBirth.year << ' ' << people[i].dateOfBirth.month << ' ' << people[i].dateOfBirth.day << endl;
	file.close();
	cout << "Дані записано у файл\n";
}

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
	for (auto i : people) cout << i.surname << ' ' << i.name << " - " << i.age << " років, народився(лась) " << i.dateOfBirth.year << '.' << i.dateOfBirth.month << '.' << i.dateOfBirth.day << endl;
}

vector<Man> addPerson(vector<Man> people) {
	string surname="---", name;
	int age;
	Year dateOfBirth;
	while (surname!="") {
		cin.ignore();
		cout << "Прізвище: ";
		getline(cin, surname);
		if (surname == "") break;
		cout << "Ім'я: ";
		getline(cin, name);
		cout << "Вік: ";
		cin >> age;
		cout << "Дата народження (через пробіл, в форматі: рік місяць день): ";
		cin >> dateOfBirth.year >> dateOfBirth.month >> dateOfBirth.day;
		Man man = { surname, name, age, dateOfBirth.year, dateOfBirth.month, dateOfBirth.day };
		people.push_back(man);
	}
	return people;
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
		for (auto i : searchedPeopleIndexes) cout << people[i].surname << ' ' << people[i].name << " - " << people[i].age << " років, народився(лась) " << people[i].dateOfBirth.year << '.' << people[i].dateOfBirth.month << '.' << people[i].dateOfBirth.day << endl;
		cout << "Хто з них вам потрібен? ";
		int choice;
		cin >> choice;
		choice--;
		return searchedPeopleIndexes[choice];
	}
}

vector<Man> deletePerson(vector<Man> people, int size) {
	string surname, name;
	cin.ignore();
	cout << "Введіть прізвище людини, яку хочете видалити: ";
	getline(cin, surname);
	cout << "Введіть ім'я людини, яку хочете видалити: ";
	getline(cin, name);
	int personToDelete = searchPerson(people, size, surname, name);
	people.erase(people.begin() + personToDelete);
	return people;
}

void showByBirthday(vector<Man> people) {
	vector<Man> birthdayPeople; //іменинники, в англійській немає спеціального слова для цього
	cout << "Введіть номер потрібного місяця: ";
	int month;
	cin >> month;
	for (auto i : people) if (i.dateOfBirth.month == month) birthdayPeople.push_back(i);
	cout << "Іменинники місяця: \n";
	showArray(birthdayPeople);
}

vector<Man> editPerson(vector<Man> people) {
	int characteristic = -1, index = 0, age, year, month, day;
	string person, surname, name;
	showArray(people);
	cin.ignore();
	cout << "Запис про яку людину ви хотіли би відрагувати? \nВведіть Фамілію та Ім'я\n";
	getline(cin, person);
	index = person.find(" ");
	surname = person.substr(0, index);
	name = person.substr(index + 1);
	index = searchPerson(people, people.size(), surname, name);
	while (characteristic!=0) {
		cout << "Яку характеристику ви хотіли ви відрагувати?\n1 - Прізвище\n2 - Ім'я\n3 - Вік\n4 - Дата народження\n0 - закінчити редагування\n";
		cin >> characteristic;
		switch (characteristic) {
		case 1:
			cin.ignore();
			cout << "Введіть нове прізвище: ";
			getline(cin, surname);
			people[index].surname = surname;
			break;
		case 2:
			cin.ignore();
			cout << "Введіть нове ім'я: ";
			getline(cin, name);
			people[index].name = name;
			break;
		case 3:
			cout << "Введіть новий вік: ";
			cin >> age;
			people[index].age = age;
			break;
		case 4:
			cout << "Введіть нову дату народження(в форматі РР ММ ДД): ";
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
		cout << "Оберіть, що хочете зробити:\n1 - Додати дані про людей\n2 - Видалити дані про людину\n3 - Сортування за прізвищем\n4 - Сортування за ім'ям\n5 - Виведення списку людей\n6 - Вивести іменинників місяця\n7 - Пошук за прізвищем та ім'ям\n8 - Редагування запису\n9 - Зберегти дані в файл\n0 - Завершити роботу і зберегти зміни\n";
		cin >> choice;
		switch (choice) {
		case 1: people = addPerson(people); break;
		case 2: people = deletePerson(people, people.size()); break;
		case 3: people = sortArray(people, people.size(), "surname"); break;
		case 4: people = sortArray(people, people.size(), "name"); break;
		case 5:
			cout << "Ось усі дані: \n";
			showArray(people);
			break;
		case 6: showByBirthday(people); break;
		case 7:
			cin.ignore();
			cout << "Введіть прізвище людини, яку хочете знайти: ";
			getline(cin, surname);
			cout << "Введіть ім'я людини, яку хочете знайти: ";
			getline(cin, name);
			index = searchPerson(people, people.size(), surname, name);
			cout << people[index].surname << ' ' << people[index].name << " - " << people[index].age << " років, народився(лась) " << people[index].dateOfBirth.year << '.' << people[index].dateOfBirth.month << '.' << people[index].dateOfBirth.day << endl;
			break;
		case 8: people = editPerson(people); break;
		case 9: writeToFile(people);
		case 0: break;
		default: cout << "Такого варіанту немає\n"; break;
		}
	}
	writeToFile(people);
	cout << "Роботу завершено! Змінені дані записано у файл\n";
	welcoming();
}
