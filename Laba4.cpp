// @authon: georgy purtov
#include <iostream>
#include <iomanip> 
#include <locale>


int main()
{
    using namespace std;
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(3);
    const int n = 5, m = 6;

    long double a[n][m] = { {-0.38, 0.88, -0.4, 0.16, 0.56, -0.79},
        {0.75, 0.88, 0.46, 0.32, 0.16, 0.07},
        {-0.68, 0.64, 0.57, -0.88, -0.4, -0.52},
        {0.48, -0.27, -0.45, -0.01, -0.65, -0.24},
        {0.64, -0.83, 0.47, -0.35, -0.5, 0.23} };
    /* невырожденную квадратную матрицу можно
представить в виде произведения двух треугольных матриц: a=BT*/   
  
   long double b[n][m];
   long double t[n][m];
/*Матрица B называется нижней треугольной матрицей, а матрица
    T называется верхней треугольной матрицей.Их элементы можно
        вычислить по явным формулам*/
    cout << "Исходная СЛАУ:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            b[i][j] = 0;
            t[i][j] = 0;
        }
    }

    // Цикл для перестановки
    if (a[0][0] == 0) { // Так как b0,0 находится в знаменателе, то необходимо выполнение условия a0, 0 ≠ 0...
        float dop = 0;
        for (int i = 1; i < n; i++) {
            if (a[i][0] != 0) {
                for (int j = 0; j < m; j++) {
                    dop = a[0][j];
                    a[0][j] = a[i][j]; // в противном случае придётся переставлять местами уравнения в исходной системе
                    a[i][j] = dop;
                }
                break;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << a[i][j] << "  ";
            cout << endl;
    }

    cout << endl;

    for (int i = 0; i < n; i++) {
        b[i][0] = a[i][0]; //  Сначала вычисляются элементы крайнего левого столбца матрицы B :
        t[i][i] = 1; 
    }

    for (int i = 1; i < n; i++) {
        t[0][i] = a[0][i]/b[0][0]; // Далее вычисляются значения элементов верхней строки матрицы T
    }


    for (int k = 1; k < n; k++) { // в едином цикле по параметру k =1 ... n − 1 вычисляются оставшиеся элементы матриц :

        for (int i = 1; i < n; i++) { 
            double sum = 0;
            for (int m = 0; m < k; m++) {
                sum = sum + b[i][m] * t[m][k];
            }
            b[i][k] = a[i][k] - sum;
        }
        if (k <= n - 2) {
            for (int j = k + 1; j < n; j++) { // (j = k + 1 ... n − 1
                double sum = 0;
                for (int m = 0; m < k; m++) {
                    sum = sum + b[k][m] * t[m][j];
                }
                t[k][j] = (a[k][j] - sum)/b[k][k];
            }
        }
    }
    
    cout << "Матрица T";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++)
            cout << t[i][j] << "  ";
            cout << endl;

    }
    cout << "\n";
    
    cout << "Матрица B";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++)
            cout << b[i][j] << "  ";
            cout << endl;
    }
    // После вычисления элементов матриц B и T необходимо перейти к решению СЛАУ.
   
    double y[n]; // Решаем систему BY = m по этапам. Сначала находим y0:
    y[0] = a[0][m - 1] / b[0][0];
    for (int i = 1; i < n; i++) { // .. а затем yi (i = 1...n − 1) :
       
        double sum = 0;
        for (int m = 0; m < i; m++)
        {
            sum = sum + b[i][m] * y[m];
        }
        y[i] = (a[i][m - 1] - sum) / b[i][i];
    }

    double x[n]; //Систему TX = Y также решаем поэтапно...
    x[n - 1] = y[n - 1]; // ... Сначала вычисляем x [n−1] ...
   
    for (int i = n-2; i >=0; i--) { // а потом оставшиеся xi (по убыванию индексов i = n − 2...0)
        double sum = 0;
        for (int m = i+1; m < n; m++)
        {
            sum = sum + t[i][m] * x[m];
        }
        x[i] = y[i] - sum;
    }

    cout << "Корни:" << endl;
    for (int i = 0; i < n; i++) {
        cout <<"x["<<i+1<<"]=" << x[i] << "\n";
    }
}
