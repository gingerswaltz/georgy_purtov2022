
#include <iostream>
#include <exception>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


class itemPricement
{
private:
  string itemName = "";
  float itemPrice = 0.0;
  int itemCount = 1;

public:

    itemPricement ()
  {
  }
  void setName (string & s1)
  {
    if (s1 == "")
      throw exception ();
    this->itemName = s1;
  }

  string const getName ()
  {
    return this->itemName;
  }

  void setPrice (float value)
  {
    if ((value < 0) || (value == NULL))
      throw exception ();

    itemPrice = value;

  }

  float const getPrice ()
  {
    return this->itemPrice;
  }

  void setCount (int value)
  {
    if ((value < 0) || (value == NULL))
      throw exception ();
    itemCount = value;
  }

  int const getCount ()
  {
    return this->itemCount;
  }

  float calcChange (float value)
  {

    if (value - itemPrice > 0)
      return value - itemPrice;
  }

  string const ToString ()
  {
    ostringstream ost;
    ost << "Name of item: " << this->itemName
      << "\t" << "Item count: " << this->itemCount
      << "\t" << "Price of 1 item: " << this->itemPrice
      << "$\t" << "Final price: " << (this->getPrice()) *
      (this->getCount()) << '\n';
    string s = ost.str ();
    return s;
  }
};




int main ()
{
  itemPricement *item = new itemPricement;
  string value = "";
  int value1 = 0;
  float value2 = 0;
  float finalprice=0.0;
  
  
  cout << "Enter name of item\n";
  cin >> value;
  item->setName (value);

  cout << "Enter count of item\n";
  cin >> value1;
  item->setCount (value1);

  cout << "Enter price of item\n";
  cin >> value2;
  item->setPrice (value2);

    finalprice=item->getPrice()*item->getCount();
  cout << "Final price is: " << finalprice << "$\n";


  while (true)
    {
      float temp = 0;
      cout << "Input your money: \n";
      cin >> temp;
      if (temp >= finalprice)
	{
	  value2 = temp;
	  break;
	}
      else
	cout << "Not enough money\n\n";
    }

  if (value2 > finalprice)
    {
      cout << "There are too much money, take your change:\n";
      cout << item->calcChange (value2) << "$\n\n";
    }


  ofstream fout;
  if (!fout)
    {
      cout << "Open File error. Check File";
    }


  fout.open ("itemPricement.txt");
  if (fout.is_open ())
    {
      fout << item->ToString ();
    }


  cout << "\t\t\tThanks for purchasing!";
    
  fout.close();
  delete item;

}
