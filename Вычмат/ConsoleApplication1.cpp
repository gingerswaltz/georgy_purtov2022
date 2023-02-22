
//// Метод половинного деления
//#include <iostream>
//#include <cmath>
//using namespace std;
//
//double f(double x)
//{
//    return 2 * exp(x) - x * x;
//}
//
//int main()
//{
//double a = -1; double b = 0; double eps = 0.0001;//    int iter = 0;
//
//   
//    while (2*(b - a) > e) {
//        
//        c = (a + b) / 2; //  Вычислим координату середины отрезка по формуле
//        if (f(b) * f(c) < 0) // В качестве следующего отрезка нужно брать отрезок..
//            a = c; // ... [c;b] если   f(b) * f(c) < 0
//        else
//            b = c; ... [a;c] если f(a) * f(c) < 0
//        ++iter; 
//    }
//    cout << "Iterations = " << iter << '\n' << "x= " << c << endl;
//    return 0;
//}

///// Метод хорд
#include <iostream>
#include <cmath>
using namespace std;
double f(double x) {
	return 2 * exp(x) - x * x;
}


int main() {
	double a = -1; double b = 0; double eps = 0.0001;
	double c;
	int iter=0;
	while (fabs(b - a) >= eps) // Считаем пока расстояние между соседними приближениями не станет меньше заданного e
	{
		++iter;
		c = a + (f(b) * (b - a)) / (f(b) - f(a)); 
		if (f(a) * f(c) < 0) // если..
		{
			b = c; // ..f(a)⋅f(c) < 0, то следующий отрезок неопределённости [a; c]
		}
		else if (f(c) * f(b) < 0) 
		{
			a = c; // и f(b) ⋅ f(c) < 0, то следующий отрезок [c; b]
		}

	}
	cout << "Iterations = " << iter << '\n' << "x= " << c << endl;
	return 0;
}
