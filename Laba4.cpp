//
#include <iostream>
#include <iomanip> // кол-во знаков после запятой
#include <locale>
#include "stdlib.h" // пауза


int main()
{
    using namespace std;
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(3);
    const int r = 5, c = 6;

    long double a[r][c] = { {-0.38, 0.88, -0.4, 0.16, 0.56, -0.79},
        {0.75, 0.88, 0.46, 0.32, 0.16, 0.07},
        {-0.68, 0.64, 0.57, -0.88, -0.4, -0.52},
        {0.48, -0.27, -0.45, -0.01, -0.65, -0.24},
        {0.64, -0.83, 0.47, -0.35, -0.5, 0.23} };
    /*Матрица B называется нижней треугольной матрицей, а матрица
    T называется верхней треугольной матрицей.Их элементы можно
        вычислить по явным формулам*/
   
   long double b[r][c];
   long double t[r][c];

    cout << "Исходная СЛАУ:" << endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            b[i][j] = 0;
            t[i][j] = 0;
        }
    }

    // Цикл для перестановки
    if (a[0][0] == 0) { // Так как b0;0 находится в знаменателе, то необходимо выполнение условия a0; 0 ≠ 0
        float dop = 0;
        for (int i = 1; i < r; i++) {
            if (a[i][0] != 0) {
                for (int j = 0; j < c; j++) {
                    dop = a[0][j];
                    a[0][j] = a[i][j];
                    a[i][j] = dop;
                }
                break;
            }
        }
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            cout << a[i][j] << "  ";
        cout << endl;
    }

    cout << endl;

    for (int i = 0; i < r; i++) {
        b[i][0] = a[i][0]; //  Сначала вычисляются элементы крайнего левого столбца матрицы B :
        t[i][i] = 1; 
    }

    for (int i = 1; i < r; i++) {
        t[0][i] = a[0][i]/b[0][0]; // Далее вычисляются значения элементов верхней строки матрицы T:
    }

    for (int k = 1; k < r; k++) { // в едином цикле по параметру k =1 ... n − 1 вычисляются оставшиеся элементы матриц :

        for (int i = 1; i < r; i++) { 
            double sum = 0;
            for (int m = 0; m < k; m++) {
                sum = sum + b[i][m] * t[m][k];
            }
            b[i][k] = a[i][k] - sum;
        }
        if (k <= r - 2) {
            for (int j = k + 1; j < r; j++) { // (j = k + 1 ... n − 1
                double sum = 0;
                for (int m = 0; m < k; m++) {
                    sum = sum + b[k][m] * t[m][j];
                }
                t[k][j] = (a[k][j] - sum)/b[k][k];
            }
        }
    }
    // После вычисления элементов матриц B и T необходимо перейти к решению СЛАУ.
   
    double y[r]; // Решаем систему BY = C по этапам. Сначала находим y0:
    y[0] = a[0][c - 1] / b[0][0];
    for (int i = 1; i < r; i++) { // .. а затем yi (i = 1...n − 1) :
       
        double sum = 0;
        for (int m = 0; m < i; m++)
        {
            sum = sum + b[i][m] * y[m];
        }
        y[i] = (a[i][c - 1] - sum) / b[i][i];
    }

    double x[r]; //Систему T X = Y также решаем поэтапно...
    x[r - 1] = y[r - 1]; // ... Сначала вычисляем x [n−1] ...
   
    for (int i = r-2; i >=0; i--) { // а потом оставшиеся xi (по убыванию индексов i = n − 2...0)
        double sum = 0;
        for (int m = i+1; m < r; m++)
        {
            sum = sum + t[i][m] * x[m];
        }
        x[i] = y[i] - sum;
    }

    cout << "Корни:" << endl;
    for (int i = 0; i < r; i++) {
        cout <<"x["<<i+1<<"]=" << x[i] << "\n";
    }
}
