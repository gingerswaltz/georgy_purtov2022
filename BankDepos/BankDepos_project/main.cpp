#include "BankDepos.h"
#include <iostream>

using namespace std;
int main(int argc, char const* argv[])
{

        string path_in = "output.txt";
        string path_out = "output.txt";
        auto y = 0; //  ввод поля даты
        auto x = 0.0;  // ввод данных
        const int size=2;
        BankDepos *deposit = new BankDepos[size]; // указатель типа BankDepos на массив из объектов BankDepos
        
       for (int i = 0; i < size; i++) {
            std::cout << "Input client lic number\n"; // ввод лицевого счета
            cin >> x;
            deposit[i].setLicNum(x); // задали лицевой счет
            std::cout << "Input client code number\n"; // ввод кода клиента
            cin >> x;
            deposit[i].setClientCode(x);// задали код клиента
            std::cout << "Input client procent number\n"; // ввод процентов
            cin >> x;
            deposit[i].set_Proc(x);// задали проценты
            std::cout << "Input client deposit money number\n"; // ввод вклада
            cin >> x;
            deposit[i].set_Money(x);// задали вклад 
            std::cout << "Input deposit day and month number\n"; // ввод даты
            cin >> x >> y;
            deposit[i].set_Date(x, y);// задали дату
            cout << "Client data: \n" << deposit[i].toString() << '\n';  // вывели все введенные данные
            try { deposit[i].fout(path_out); } // вывод в файл.
            catch (const runtime_error& err) { cout << err.what(); } 
       }
       BankDepos *depos_mass1[size]; // статический массив из указателей на объект

       for (int i = 0; i < size; i++) depos_mass1[i] = new BankDepos;/* depos_mass1[i];*/
       for (int i = 0; i < size; i++) {
           cout << '\n' << "Record N" << i << ": " << depos_mass1[i]->toString(); // стрелочка разыменовывает указатель  и вызывает метод.
       }
       
        
       
        BankDepos deposit2;
        deposit2 = deposit2.fin(path_in);
        cout << "Client data from file: \t" << deposit2.toString() << '\n';  // вывели все введенные данные
        delete[] deposit; // освобождение памяти.
        for (int i = 0; i < size; i++) delete depos_mass1[i]; // удаление каждого элемента
        return 0;
}
           
           
             

        
           
  
 