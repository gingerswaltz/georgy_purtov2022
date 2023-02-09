
#include <string>
#include "Building.h"
using namespace std;
string btos(bool x) // bool to string
{
    if (x) return "True";
    return "False";
};
   Building::Building() { // конструктор 1
        this->fundament = "Example";
        this->floor = 3;
        this->window = 2;
        this->door = 1;
        this->wall = "Example1";
        this->roof = "Example2";
    }
   string Building::getFundament() const { return fundament; };
   string Building::getWall() const { return wall; };
   string Building::getRoof() const { return roof; };
   int Building::getFloor() const { return floor; };
   int Building::getWindow() const { return window; };
   int Building::getDoor() const { return door; };
   void Building::setFundament(const string& s1) { if (s1 == "") throw invalid_argument("IS empty");  fundament =s1 ; }
   void Building::setWall(const string& s1) { if (s1 == "") throw invalid_argument("IS empty");  wall = s1; }
   void Building::setRoof(const string& s1) { if (s1 == "") throw invalid_argument("IS empty");  roof = s1; }
   void Building::setFloor(int x)
   {
       if (x < 0) 
           throw invalid_argument("Floor is negative"); 
           floor = x;
       };

   void Building::setWindow(unsigned int x) { window = x; }
   void Building::setDoor(unsigned int x) { door =x; }
   string Building::to_string()// virtual tostring {anything else}
   {
       ostringstream ost;
       ost <<"Fundament " << this->fundament << "\t" << "Wall " << this->wall << "\t " << "Roof " << this->roof << " \t" <<
           "Floor " << this->floor << " \t" << "Windows "<<this->window << " \t" <<"Doors " <<this->door << '\n';
       string s = ost.str();
       return s;
   }
   
    House::House() { // конструктор 1
        this->fundament = "Example3";
        this->floor = 5;
        this->window = 4;
        this->door = 3;
        this->wall = "Example4";
        this->roof = "Example5";
        this->room = 2;
        this->heating = "Example6";
        this->garden = false;
    }
    
    string House::getHeating() const { return heating; }
    int House::getRoom() const { return room; }
    bool House::getGarden() const { return garden; }
    void House::setHeating(const string& s1) { heating =s1 ; }
    void House::setRoom(unsigned int x) { room = x; }
    void House::setGarden(bool x) { garden =x ; }
    string House::to_string()  {
        return Building::to_string() + "Heating " + this->heating +"\tGarden "+btos(this->garden)+"\tRoom "+std::to_string(this->room);
    }

   
    Office::Office() { // конструктор 1
        this->fundament = "Example7";
        this->floor = 6;
        this->window = 5;
        this->door = 4;
        this->wall = "Example8";
        this->roof = "Example9";
        this->cabinet = 2;
        this->equipment =false;
        this->phone = false;
    }

    bool Office::getEquip() const { return equipment; }
    int Office::getCabinet() const { return cabinet; }
    bool Office::getPhone() const { return phone; }
    void Office::setEquip(bool x) { equipment = x; }
    void Office::setCabinet(unsigned int x) { cabinet = x; }
    void Office::setPhone(bool x) { phone = x; }
    string Office::to_string() {
    return Building::to_string() + "Equip " + btos(this->equipment) + "\tPhone " + btos(this->phone) + "\tCabinets " + std::to_string(this->cabinet);
    }
    