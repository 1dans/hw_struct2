#include <iostream>
#include "main.h"
#include "task1.h"
#include "task2.h"
using namespace std;

void welcoming()
{
	cout << "³���! ��� �������� �� ����� �� �������? \n1 - ��������\n2 - ���������� ��� �����\nq - �����\n��� ����: ";
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
		default: cout << "������ ������� ����. ��������� �� ��� (1/2/q): "; break;
		}
	}
	cout << "�������!";
}
