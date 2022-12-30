//
// Created by Georgy Purtov on 25.10.2022.
//
#include "BankDepos.h"
#include <iostream>

BankDepos::BankDepos() { // конструктор 1
    this->money=0; // this-> так объект называет себя внутри класса..
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
    if (x > 9999) throw invalid_argument("License number is invalid!");
    lic = x;
}

int BankDepos::getClientCode()const {
    return code;
}

void BankDepos::setClientCode(unsigned short x) {
    if (x > 9999) throw invalid_argument("Code number is invalid!");
    code = x;
}

float BankDepos::get_Proc()const {
    return proc;
}

void BankDepos::set_Proc(float x) {
    if (x < 0) throw invalid_argument("Procent number is too little!");
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



float BankDepos::get_Money()const {
    return money;
}

void BankDepos::set_Money(float x) {
    money = x;
}

void BankDepos::change(float money_c) {
    money = money + money_c;
};

BankDepos BankDepos::fin(const string& path_in) {
    ifstream fin;
    fin.open(path_in);
    //TODO:: TRYCATCH , THIS-> (delete return!) переименовать.
    if (!fin.is_open()) { std::cout << "Open file error" << endl; }
    else
        std::cout << "File in is opened!" << endl;
    fin.read((char*)&money, sizeof(float));
    fin.read((char*)&proc, sizeof(float));
    fin.read((char*)&code, sizeof(int));
    fin.read((char*)&lic, sizeof(int));
    fin.read((char*)&date_Depos.day, sizeof(int));
    fin.read((char*)&date_Depos.month, sizeof(int));

    set_Money(money+1);
    set_Proc(proc+1);
    setClientCode(code);
    setLicNum(lic);
    set_Date(date_Depos.day, date_Depos.month);
    // инициализировать второй обьект в мейн, получить обьект депозит_файл с функции
    fin.close();
}

void BankDepos::fout(const string& path_out) {
    ofstream fout;
    fout.open(path_out, ofstream::trunc);
    if (!fout.is_open()) { throw runtime_error("Open file error"); }
    else
        std::cout << "File out is opened!" << endl;
    fout.write((char*)&(this->money), sizeof(float));
    fout.write((char*)&(this->proc), sizeof(float));
    fout.write((char*)&(this->code), sizeof(int));
    fout.write((char*)&(this->lic), sizeof(int));
    fout.write((char*)&(this->date_Depos.day), sizeof(int));
    fout.write((char*)&(this->date_Depos.month), sizeof(int));
    fout.close();
};