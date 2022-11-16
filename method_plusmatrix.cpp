///@author: georgy purtov
#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;		// пространство имён 

int main()
{
	system("chcp 1251"); // кодировка на всякий случай. в маке не работает?
	system("cls");
	int rows = 4, cols = 8; // строки, столбцы
	int k = 0;				// шаги цикла
	int m = 0;
	float e = 0.0000001;	// чиселко которое нам не надо (меньше 0 грубо говоря)

	float arr[4][8] = 
	{ {	4,	2,	8,	9,	1,	0,	0,	0},
	{	9,	6,	7,	1,	0,	1,	0,	0},
	{	5,	3,	9,	9,	0,	0,	1,	0},
	{	5,	7,	8,	2,	0,	0,	0,	1}};

	cout << "Изначальная матрица" << endl;
	// выводим для проверки
	for (int a = 0; a < rows; a++) // Вывод матрицы
	{
		cout << "|";
		for (int r = 0; r < cols; r++)
		{
			cout << setw(12) << arr[a][r] << "|";
		}
		cout << endl;
	}
	cout << endl;

	while (k < rows)
	{
		if (fabs(arr[k][k]) < e)					// если на главной диагонали 0
		{
			for (int i = k; i < rows; i++)			//Смотрим эллементы ниже
			{
				if (arr[i][k] != 0 && m == 0)		//проверяем на не ноль
				{
					m = 1;
					for (int j = 0; j < cols; j++)	//замена строк местами
					{
						arr[k][j] += arr[i][j];		//меняем нижнюю строку на верхнюю 
					}
				}
			}

			//выводим для проверки
			cout << "Убрали 0 в главной диагонали" << endl;
			for (int a = 0; a < rows; a++) //Вывод матрицы
			{
				cout << "|";
				for (int r = 0; r < cols; r++)
				{
					cout << setw(12) << arr[a][r] << "|";
				}
				cout << endl;
			}
			cout << endl;
		}

		for (int i = 0; i < rows; i++)		//перебор строк
		{
			for (int j = 0; j < cols; j++)	// перебор столбцов
			{
				if (i != k && k < j)		//заполнение по формуле Жордана-Гаусса (правило прямоугольника)
				{
					arr[i][j] = (arr[i][j] * arr[k][k] - arr[i][k] * arr[k][j]) / arr[k][k];
				}
			}
		}

		for (int i = 0; i < rows; i++)	//обнуление элементов k - го столбца
		{
			if (i != k)					
			{
				arr[i][k] = 0;			//обнуление эллементов столбца
			}
		}

		for (int j = cols - 1; j >= k; j--) // Делим k-ю строку на a[k,k], спускаясь вниз
		{
			arr[k][j] = (arr[k][j] / arr[k][k]);
		}

		for (int i = 0; i < rows; i++)		//Вывод матрицы
		{
			cout << "|";
			for (int j = 0; j < cols; j++)
			{
				cout << setw(12) << arr[i][j] << "|";
			}
			cout << endl;
		}
		cout << endl;

		k++;
	}
}