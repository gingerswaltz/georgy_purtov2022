namespace BankDeposit;
using System;

public class BankDepos /// Класс описывающий банковский вклад
{
    const double eps = 0.01; // Чиселко точности для процентов, потому что проценты могут быть ниже 0
    private double _money; // Деньги
    private double _proc; // Проценты
    private uint _licnum; // Лицевой счет
    private uint _codenum; // Код клиента

    // Конструктор 1
    public BankDepos(double money, double proc, uint codenum, uint licnum)
    {
        _money = money;
        _proc = proc;
        _codenum = codenum;
        _licnum = licnum;
        
        
    }
    
    // Конструктор 2
    public BankDepos()
    {
        _money = 1;
        _proc = 1;
        _codenum = 1111;
        _licnum = 2222;
        
    }

    // сеттер денег
    public void setMoney(double value)
    {
        if (value < 0)
            throw new ArgumentException("Too litle");
        else
       _money = value;
    }
    // геттер денег
    public double getMoney() { return _money; }

    // сеттер процентов
    public void setProc(double value)
    {
        if ((value < eps) || (value>10))
            throw new ArgumentException("Wrong Procents");
        else 
            _proc = value;
    }
    // геттер процентов
    public double getProc() { return _proc; }

    // сеттер кода клиента
    public void setcodeNum(uint value)
    {
        if (value > 9999) throw new ArgumentException("Wrong Number");
        else 
            _codenum = value;
    }
    
    // геттер кода клиента
    public uint getcodeNum() { return _codenum; }

    // сеттер лицевого счета
    public void setlicNum(uint value)
    {
        if (value > 9999) throw new ArgumentException("Wrong Number");
        else
            _licnum = value;
    }

    // геттер лицевого счета
    public uint getlicNum() { return _licnum; }
    

    // изменение суммы счета клиента
    public void MoneyChange(double value)
    {
        _money += value;        
    }


    // Вывод данных объекта
    public override string ToString()
    {
        return $"Client license number: {_licnum}\n" +
            $"Client Code Number: {_codenum}\n" +
            $"Client procents: {_proc}%\n" +
            $"Client money deposit: {_money}$\n" +
            $"Client date of deposit: {DateTime.Now.Day} day, {DateTime.Now.Month} month, {DateTime.Now.Year} year\n";

    }

}
