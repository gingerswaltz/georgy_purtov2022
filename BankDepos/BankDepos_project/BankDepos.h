//
// Created by Georgy Purtov on 25.10.2022.
//

#pragma once
#include <sstream> // конвертеры
#include <string>
#include <fstream>
using namespace std;

struct Date {
    unsigned short day = 1;
    unsigned short month = 1;
};

class BankDepos { // Реализация банковского вклада.
    float money,proc; // поля денег вклада и процентов
    int lic, code;  // поля лицевого счета и кода клиента
    Date date_Depos; // поле даты вклада
public:
    BankDepos(); // Конструктор1
    BankDepos(short lic, short code, short proc, float money, Date date_Depos);  // Конструктор2
    int getLicNum() const; // получить лицевой счет
    void setLicNum(unsigned short x); // задать лицевой счет
    int getClientCode()const; // Получить код клиента
    void setClientCode(unsigned short x); // Задать код клиента
    float get_Proc()const; // Получить проценты
    void set_Proc(float x); // Задать проценты
    Date get_Date()const; // Получить дату
    void set_Date(unsigned short x, unsigned short y); // Задать дату
    float get_Money()const; // Получить вклад
    void set_Money(float x); // Задать вклад
    void change(float money_c); // Изменение текущего вклада
    string toString(); // Конвертация в строку данных
    void fout(const string& path_out); // вывод в файл объекта
    BankDepos fin(const string& path_in); // ввод из файла
};


