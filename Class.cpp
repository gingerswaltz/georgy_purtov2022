//
// Created by Georgy Purtov on 25.10.2022.
//
#include "Class.h"
#include <iostream>


BankDepos::BankDepos() { // конструктор 1
    this->money=0; 
    this->lic = 0;
    this->code = 0;
    this->proc = 1;
    this->date_Depos.day=1; 
    this->date_Depos.month = 1;
}

BankDepos::BankDepos (short lic1, short code1, short proc1, float money1, Date date_Depos1) {
    setLicNum(lic1);
    setClientCode(code);
    set_Proc(proc);
    set_Money(money);
} // Конструктор2     

string BankDepos::toString() {

    ostringstream ost;
    ost <<"Client license number: " <<this->lic
    << "; Client code number:" << this->code
    <<"; Client procents:"<<this->proc
    <<"%; Client money deposit:"
    <<this->money<<"$; \n"
    <<"Date of deposit:"<<date_Depos.day<<"d "<<date_Depos.month<<"m \n";
    string s = ost.str();
    return s;

}

int BankDepos::getLicNum() const {  // все методы которые не меняют поля константные
    return lic;
}

void BankDepos::setLicNum(unsigned short x) {  // прописать везде unsigned short кроме money
    if (x > 9999 && x <= 99999) throw invalid_argument("License number is invalid!");
    lic = x;
}

int BankDepos::getClientCode()const {
    return code;
}

void BankDepos::setClientCode(unsigned short x) {
    if (x > 99999 && x <= 999999) throw invalid_argument("Client code number is too big!");
    code = x;
}

int BankDepos::get_Proc()const {
    return proc;
}

void BankDepos::set_Proc(float x) {
    if (x < 0 && x == 0) throw invalid_argument("Procent number is too little!");
    proc = x;
}

Date BankDepos::get_Date()const { // вернем значение типа struct …

    return date_Depos; 

}

void BankDepos::set_Date(unsigned short x, unsigned short y) {
    if (x<1) throw invalid_argument("Day number is too little!");
    if (y<1) throw invalid_argument("Month number is too little!");
    if (x>31) throw invalid_argument("Day number is too big!");
    if (x>12) throw invalid_argument("Month number is too big!");
    date_Depos.day = x;
    date_Depos.month = y;
}



int BankDepos::get_Money()const {
    return money;
}

void BankDepos::set_Money(float x) {
    money = x;
}

void BankDepos::change(float money_c) {
    money = money + money_c;
};


