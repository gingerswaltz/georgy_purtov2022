#include "Class.h"
#include <iostream>
using namespace std;
int main(int argc, char const* argv[])
{
    string s_check ="y";
   
    do {
        BankDepos deposit; // инициализировали объект
        auto y = 0; //  ввод поля даты
        auto x = 0.0;  // ввод данных
        string s; // строка для ввода согласия или отказа (y/n)
        std::cout << "Input client lic number\n"; // ввод лицевого счета
        cin >> x;
        deposit.setLicNum(x); // задали лицевой счет
        std::cout << "Input client code number\n"; // ввод кода клиента
        cin >> x;
        deposit.setClientCode(x);// задали код клиента
        std::cout << "Input client procent number\n"; // ввод процентов
        cin >> x;
        deposit.set_Proc(x);// задали проценты
        std::cout << "Input client deposit money number\n"; // ввод вклада
        cin >> x;
        deposit.set_Money(x);// задали вклад 
        std::cout << "Input deposit day and month number\n"; // ввод даты
        cin >> x >> y;
        deposit.set_Date(x, y);// задали дату
        cout << "Client data: \n" << deposit.toString() << '\n';  // вывели все введенные данные
        std::cout << "Change the deposit? Print y/n\n"; // диалог на добавление/изымание денег вклада
        std::cin >> s;
        unsigned n; // флаг-переменная 
        if (s == "y") n = 1; else n = 0;
        switch (n) // переключение N по значениям:
        {
        case 1: { // 1: вводим новое число денег (изымаем или добавляем), 
            //затем вызываем соответствующий метод и получаем новое значение вклада
            auto money_c = 0.0;
            std::cout << "Enter the number of changing:";
            std::cin >> money_c;
            deposit.change(money_c);
            std::cout << "New amount of deposit:" << deposit.get_Money() << '\n';

        }
        case 0: // 0: switch завершается
            break;
        }
        std::cout << "Add new deposit? Print y/n\n"; // диалог на добавление вклада
        std::cin >> s_check;
        if (s_check == "n") return 0;
    } while ((s_check != "n") or (s_check != "N"));

}