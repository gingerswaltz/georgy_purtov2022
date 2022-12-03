#include "Building.h"
/// можно ли записать объект базового класса в объект производного и наоборот
int main() {
	Building * building = new Building(); // инициализация класса основного
	House* house = new House(); // инициализация класса наследника 1
	Building* building1 = house; // полиморфизм 1 (? не знаю зачем нужно уточнить у преподавателя)
	Office* office = new Office(); // инициализация класса наследника 2
	Building* building2 = office; // полиморфизм 2


	cout << building->to_string() << endl << endl;  // Класс основной. Вызов to_string из Bulding

	cout << building1->to_string() << endl << endl; // Класс наследник 1. Вызов to_string из House

	cout << building2->to_string() << endl; // Класс наследник 2. Вызов to_string из Office

	delete building; delete building1; delete building2; // очистка памяти
	return 0;
}