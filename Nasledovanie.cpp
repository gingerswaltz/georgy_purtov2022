#include <string>
using namespace std;
class Building
{
public:
    string fundament;
    int floor;
    int window;
    int door;

    Building::Building() { // конструктор 1
     fundament=" ";
     floor=1;
     window=0;
     door=0;
}
 
    string getFundament() const { return fundament; }
    int getFloor() const { return floor; }
    int getWindow() const { return window; }
    int getDoor() const { return door; }

 
};
class House: public Building
{
public:
    int room; // кол-во комнат
    string heating; // тип отопления
    bool garden; // наличие сада да или нет

    Building::House() { // конструктор 1
     fundament=" ";
     floor=1;
     window=0;
     door=0;
     room=0;
     heating=" ";
     garden=false;
}
 
    string getHeating() const { return heating; }
    int getRoom() const { return room; }
    bool getGarden() const { return garden; }

 
};

class Office: public Building
{
public:
    int cabinet; // кол-во офисов
    string heating; // тип отопления
    bool garden; // наличие сада да или нет

    Building::House() { // конструктор 1
     fundament=" ";
     floor=1;
     window=0;
     door=0;
     room=0;
     heating=" ";
     garden=false;
}
 
    string getHeating() const { return heating; }
    int getRoom() const { return room; }
    bool getGarden() const { return garden; }

 
};