#include "pch.h"
#include "..\BankDepos_project\Class.h"
/*  this->money=0; v
    this->lic = 0;  v
    this->code = 0; v
    this->proc = 1; v
    this->date_Depos.day=1;v 
    this->date_Depos.month = 1; v 
*/

TEST(BankDepos, set_Money) {
  BankDepos test_Bank;
  test_Bank.set_Money(10);
  EXPECT_EQ(test_Bank.get_Money(), 10);
}

TEST(BankDepos, set_Lic) {
  BankDepos test_Bank;
  test_Bank.setLicNum(10);
  EXPECT_EQ(test_Bank.getLicNum(), 10);

  test_Bank.setLicNum(8740);
  EXPECT_EQ(test_Bank.getLicNum(), 8740);


}

TEST(BankDepos, set_Code) {
  BankDepos test_Bank;
  test_Bank.setClientCode(10);
  EXPECT_EQ(test_Bank.getClientCode(), 10);

}

TEST(BankDepos, lic_exception) {
	BankDepos test_Bank;

	EXPECT_THROW(test_Bank.setLicNum(99999), invalid_argument);

}

TEST(BankDepos, code_exception) {
	BankDepos test_Bank;
	EXPECT_THROW(test_Bank.setClientCode(99999), invalid_argument);
}
TEST(BankDepos, set_Proc) {
  BankDepos test_Bank;
  test_Bank.set_Proc(10);
  EXPECT_EQ(test_Bank.get_Proc(), 10);
}

TEST(BankDepos, set_Date_day) {
	BankDepos test_Bank;
	test_Bank.set_Date(1,1);
	EXPECT_EQ(test_Bank.get_Date().day, 1);
	EXPECT_EQ(test_Bank.get_Date().month, 1);

}



TEST(BankDepos, getLicnum) {
	BankDepos test_Bank;
	EXPECT_EQ(test_Bank.getClientCode(), 0);
}

TEST(BankDepos, getClientCode) {
	BankDepos test_Bank;
	EXPECT_EQ(test_Bank.getClientCode(), 0);
}
TEST(BankDepos, get_Proc) {
	BankDepos test_Bank;
	EXPECT_EQ(test_Bank.get_Proc(), 1);
}

TEST(BankDepos, get_Money) {
	BankDepos test_Bank;
	EXPECT_EQ(test_Bank.get_Money(), 0);
}

TEST(BankDepos, get_Date_month) {
	BankDepos test_Bank;
	EXPECT_EQ(test_Bank.get_Date().month, 1);
}
TEST(BankDepos, get_Date_day) {
	BankDepos test_Bank;
	EXPECT_EQ(test_Bank.get_Date().day, 1);
}
TEST(BankDepos, change_Deposit) {
	BankDepos test_Bank;
	auto x = 0.0;
	test_Bank.set_Money(x);
	auto test = 300.0;
	test_Bank.change(test);
	EXPECT_EQ(test_Bank.get_Money(), 300);
}
