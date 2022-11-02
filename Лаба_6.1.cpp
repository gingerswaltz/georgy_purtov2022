// Метод простых итераций
#include <iostream>
#include <iomanip>	// для setw()
#include <string>	// для stoi() (перевод строки в число
#include <fstream>  // для файла
#include <vector>   // для векторов

using namespace std;

void output(const vector <vector<float>>& vec) // вывод матрицы векторов
{
	cout << endl;
	//выводим для проверки
	for (int i = 0; i < vec.size(); i++) //Вывод матрицы
	{
		cout << "|";
		for (int j = 0; j < vec[i].size(); j++)
			cout << setw(12) << vec[i][j] << "|";
		cout << endl;
	}
	cout << endl;
}

int main()
{
	system("chcp 1251");
	system("cls");

	float e = 0.001;					// точность
	cout << "Точность= " << e << endl;

	vector <vector<float>> vec_a =	// создаём массив массивов векторов для матода простых итераций
	{{33,	7,		5,		1,		9,		45},
	{2,		36,		9,		6,		4,		30},
	{6,		1,		31,		8,		4,		144},
	{4,		2,		7,		20,		3,		48},
	{6,		6,		9,		3,		28,		52} };

	/*33x1 `7x2 ´5x3 `x4 `9x5 “ 45;
´2x1 `36x2 ´9x3 ´6x4 ´4x5 “ 30;
6x1 ´x2 `31x3 `8x4 `4x5 “ 144;
´4x1 ´2x2 `7x3 `20x4 `3x5 “ 48;
6x1 `6x2 `9x3 `3x4 `28x5 “ 52:*/

	vector <vector<float>> vec_x;				// корни для матода простых итераций
	vector<float> vec_temp = { 0,0,0,0,0 };		// временный вектор
	vec_x.push_back(vec_temp);					// временный вектор в конец  вектора корней 

	cout << endl << "Исходная матрица\n";
	output(vec_a);		// вывод вектора

	int m;				// для подсчёта эллементов подходящей точности
	float temp;			//временная переменная
	int k = 0;			//шаги цикла

	bool flag = true;	// для бесконечного цикла
	while (flag)		// цикл шагов 
	{
		m = 0;						// обнуляем
		vec_x.push_back(vec_temp);	// увеличиваем размерность матрицы vec_x

		for (int i = 0; i < vec_a.size(); i++) // цикл для использования i-х эллементов матриц
		{
			temp = 0;	// обнуляем
			for (int j = 0; j < vec_a.size(); j++) // цикл для рассчёт суммы
			{
				if (j!=i)
					temp += -(vec_a[i][j] * vec_x[k][j]);							// по формуле
			}
			vec_x[k + 1][i] = 1 / vec_a[i][i] * (vec_a[i][vec_a.size()] + temp);	// по формуле

			if (fabs(vec_x[k + 1][i] - vec_x[k][i]) >= e)	// проверка точности
				m = 1;										// если не точно - меняем m
		}

		if (m == 0)			// если m не поменялась
			flag = false;	// остановка цикла

		k += 1;				// счётчик цикла
	}
	
	cout << endl << "Матрица X";
	output(vec_x);	// вывод метрицы

	for (int i = 0; i < vec_temp.size(); i++)	// выводим точность
	{
		e = fabs(vec_x[k][i] - vec_x[k-1][i]);
		cout << "E= " << e << endl;
	}

	for (int i = 0; i < vec_temp.size(); i++)	// вывод решения
		cout << "X" << "[" << vec_x.size() - 1 << "]" << "[" << i << "]=|" << vec_x[vec_x.size() - 1][i] << "|  ";
	cout << endl;
}