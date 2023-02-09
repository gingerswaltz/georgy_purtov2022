///@author: georgy purtov;
#pragma once
#include <iostream>
#include <sstream>
using namespace std;
/// Класс реализации постройки здания
class Building 
{
protected:
    string fundament; // Фундамент
    int floor;        // Кол-во этажей
    int window;       // Кол-во окон
    int door;         // Кол-во дверей
    string wall;      // Тип стен
    string roof;      // Тип крыши

    
public:
    Building(); // Конструктор
    string getFundament() const; // Получить тип фундамента
    string getWall() const; // Получить тип стен
    string getRoof() const; // Получить тип крыши 
    int getFloor() const; // Получить кол-во этажей
    int getWindow() const; // Получить кол-во окон
    int getDoor() const; // Получить кол-во дверей
    void setFundament(const string &s1); // Задать фундамент
    void setWall(const string& s1);  // Задать стены
    void setRoof(const string& s1);  // Задать крышу
    void setFloor(int x); // Задать этажи
    void setWindow(unsigned int x); // Задать окна
    void setDoor(unsigned int x); // Задать двери
    virtual string to_string(); // Виртуальный метод : Вывод всех данных
};


class House : public Building
{
protected:
    int room; // кол-во комнат
    string heating; // тип отопления
    bool garden; // наличие сада да или нет
public:
    House(); // конструктор
    string getHeating() const; // Получить тип отопления
    int getRoom() const; // Получить кол-во окон
    bool getGarden() const; // Получить наличие сада
    void setHeating(const string& s1); // Задать тип отопления
    void setRoom(unsigned int x); // Задать комнаты
    void setGarden(bool x); // Задать наличие сада
    string to_string(); // Получение всех данных 
};

class Office : public Building
{
protected:
    int cabinet; // кол-во офисов
    bool equipment; // наличие оборудования офиса
    bool phone; // наличие телефонной линии да или нет
public:
    Office(); // конструктор
    bool getEquip() const; // Получить наличие оборудования
    int getCabinet() const; // Получить кол-во кабинетов
    bool getPhone() const; // получить наличие телефонной линии
    void setEquip(bool x); // Задать наличие офисного оборудования
    void setCabinet(unsigned int x); // Задать кол-во кабинетов
    void setPhone(bool x);// Задать телефонную линию 
    string to_string(); // Получение всех данных 
}; 
   
