#include <iostream>
#include "main.h"
#include "task1.h"
#include "task2.h"
using namespace std;

void welcoming()
{
	cout << "Вітаю! Яке завдання ви хотіли би вивести? \n1 - студенти\n2 - інформація про людей\nq - вихід\nВаш вибір: ";
}

int main()
{
	system("chcp 1251 > null");
	welcoming();
	char choice = ' ';
	while (choice!='q') {
		cin >> choice;
		switch (choice) {
		case '1': task1(); break;
		case '2': task2(); break;
		case 'q': break;
		default: cout << "Такого варіанту немає. Спробуйте ще раз (1/2/q): "; break;
		}
	}
	cout << "Бувайте!";
}
