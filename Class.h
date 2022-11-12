//
// Created by Georgy Purtov on 25.10.2022.
//

#ifndef CLASS_PROJECT_CLASS_H
#define CLASS_PROJECT_CLASS_H
#include <sstream> // конвертеры
#include <string>
using namespace std;

struct Date {
    unsigned short day = 1;
    unsigned short month = 1;
};

class BankDepos {
    float money,proc;
    int lic, code; 
    Date date_Depos;
public:
    BankDepos(); // Конструктор1
    BankDepos(short lic, short code, short proc, float money, Date date_Depos);  // Конструктор2
    int getLicNum() const; // получить лицевой счет
    void setLicNum(unsigned short x); // задать лицевой счет
    int getClientCode()const; // Получить код клиента
    void setClientCode(unsigned short x); // Задать код клиента
    int get_Proc()const; // Получить проценты
    void set_Proc(float x); // Задать проценты
    Date get_Date()const; // Получить дату
    void set_Date(unsigned short x, unsigned short y); // Задать дату
    int get_Money()const; // Получить вклад
    void set_Money(float x); // Задать вклад
    void change(float money_c); // Изменение текущего вклада
    string toString(); // Конвертация в строку данных
};

#endif //CLASS_PROJECT_CLASS_H
