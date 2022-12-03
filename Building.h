///@author: georgy purtov;
#pragma once
#include <iostream>
#include <sstream>
using namespace std;
/// ����� ���������� ��������� ������
class Building 
{
protected:
    string fundament; // ���������
    int floor;        // ���-�� ������
    int window;       // ���-�� ����
    int door;         // ���-�� ������
    string wall;      // ��� ����
    string roof;      // ��� �����

    
public:
    Building(); // �����������
    string getFundament() const; // �������� ��� ����������
    string getWall() const; // �������� ��� ����
    string getRoof() const; // �������� ��� ����� 
    int getFloor() const; // �������� ���-�� ������
    int getWindow() const; // �������� ���-�� ����
    int getDoor() const; // �������� ���-�� ������
    void setFundament(const string &s1); // ������ ���������
    void setWall(const string& s1);  // ������ �����
    void setRoof(const string& s1);  // ������ �����
    void setFloor(int x); // ������ �����
    void setWindow(unsigned int x); // ������ ����
    void setDoor(unsigned int x); // ������ �����
    virtual string to_string(); // ����������� ����� : ����� ���� ������
};


class House : public Building
{
protected:
    int room; // ���-�� ������
    string heating; // ��� ���������
    bool garden; // ������� ���� �� ��� ���
public:
    House(); // �����������
    string getHeating() const; // �������� ��� ���������
    int getRoom() const; // �������� ���-�� ����
    bool getGarden() const; // �������� ������� ����
    void setHeating(const string& s1); // ������ ��� ���������
    void setRoom(unsigned int x); // ������ �������
    void setGarden(bool x); // ������ ������� ����
    string to_string(); // ��������� ���� ������ 
};

class Office : public Building
{
protected:
    int cabinet; // ���-�� ������
    bool equipment; // ������� ������������ �����
    bool phone; // ������� ���������� ����� �� ��� ���
public:
    Office(); // �����������
    bool getEquip() const; // �������� ������� ������������
    int getCabinet() const; // �������� ���-�� ���������
    bool getPhone() const; // �������� ������� ���������� �����
    void setEquip(bool x); // ������ ������� �������� ������������
    void setCabinet(unsigned int x); // ������ ���-�� ���������
    void setPhone(bool x);// ������ ���������� ����� 
    string to_string(); // ��������� ���� ������ 
}; 
   
