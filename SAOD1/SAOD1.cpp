
#include <iostream>
#include <exception>
#include <string>
#include <fstream>
using namespace std;


class itemPricement 
{
private:
	string itemName="";
	float itemPrice=0.0;
	int itemCount = 1;

public:
	
	itemPricement() 
	{
	}
	void setName(string& const s1) 
	{
		if (s1 == "") throw exception("Name is empty");
		this->itemName = s1;
	}

	string const getName ()
	{
		return this->itemName;
	}

	void setPrice(float value)
	{
		if ((value < 0) || (value == NULL))
			throw exception("Price is invalid");

		itemPrice = value;

	}

	float const getPrice()
	{
		return this->itemPrice;
	}

	void setCount(int value)
	{
		if ((value < 0) || (value == NULL))
			throw exception("Count is invalid");
		itemCount = value;
	}

	int const getCount()
	{
		return this->itemCount;
	}

	float calcChange(float value)
	{
		
		if (value - itemPrice>0)
		return value - itemPrice;
	}
};



int main()
{
	itemPricement* item = new itemPricement;
	string value = "";
	int value1=0;
	float value2=0;

	cout << "Enter name of item\n";
	cin >> value;
	item->setName(value);

	cout << "Enter count of item\n";
	cin >> value1;
	item->setCount(value1);
	
	cout << "Enter price of item\n";
	cin >> value2;
	item->setPrice(value2 * item->getCount());

	cout << "Final price is: " << item->getPrice() << "$\n";


	while (true)
	{
		float temp = 0;
		cout << "Input your money: \n";
		cin >> temp;
		if (temp >= item->getPrice())
		{
			value2 = temp;
			break;
		}
		else cout << "Not enough money\n\n";
	}

	if (value2 > item->getPrice())
	{ 
		cout << "There are too much money, take your change:\n";
		cout << item->calcChange(value2)<<"$\n\n";
	}
	
	fstream fin;


	cout << "\t\t\tThanks for purchasing!";
	
	delete item;

}
