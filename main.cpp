#include "Building.h"
/// ����� �� �������� ������ �������� ������ � ������ ������������ � ��������
int main() {
	Building * building = new Building(); // ������������� ������ ���������
	House* house = new House(); // ������������� ������ ���������� 1
	Building* building1 = house; // ����������� 1 (? �� ���� ����� ����� �������� � �������������)
	Office* office = new Office(); // ������������� ������ ���������� 2
	Building* building2 = office; // ����������� 2


	cout << building->to_string() << endl << endl;  // ����� ��������. ����� to_string �� Bulding

	cout << building1->to_string() << endl << endl; // ����� ��������� 1. ����� to_string �� House

	cout << building2->to_string() << endl; // ����� ��������� 2. ����� to_string �� Office

	delete building; delete building1; delete building2; // ������� ������
	return 0;
}