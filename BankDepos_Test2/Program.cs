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
    public BankDepos(double money, double proc, uint licnum, uint codenum, uint value1, uint value2)
    {
        _money = money;
        _proc = proc;
        _licnum = licnum;
        _codenum = codenum;
        
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


public class Program // основной класс
{
    public static void Main(string[] args) 
    {
        uint x = 1; // for int value
        double y = 1.0; // for float value
        string s; // для считывания символа отказа или согласия дальше
        
        /// Хранение объектов реализовано через коллекцию List 
        List<BankDepos> Deposit= new List<BankDepos>();

        while (true) // бесконечный цикл для ввода данных
        {
            Console.WriteLine("Add deposit? Type n to cancel or press any key to continue");
            s = Console.ReadLine(); // считаем символ
            if ((s == "n") || (s.ToLower() == "n")) { break; }
            
            else
            {
                BankDepos depos1 = new BankDepos(); // инициализируем объект который потом закинем в список

                Console.WriteLine("Enter code number (up to 4 digits): "); // ввод кода клиента
                x = (uint)Convert.ToInt32(Console.ReadLine());
                depos1.setcodeNum(x);

                Console.WriteLine("Enter lic number (up to 4 digits): ");  // ввод лицевого счета клиента
                x = (uint)Convert.ToInt32(Console.ReadLine());
                depos1.setlicNum(x);

                Console.WriteLine("Enter procents: ");  // ввод процентов
                y = Convert.ToDouble(Console.ReadLine());
                depos1.setProc(y);

                Console.WriteLine("Enter amount of cash: "); // ввод денег
                y = Convert.ToDouble(Console.ReadLine());
                depos1.setMoney(y);

                Deposit.Add(depos1); // вставить новый объект в список 
            }

                

            
        }
        int count = 0; // счетчик
        foreach (BankDepos deposit in Deposit)  // цикл по элементам коллекции 
        {
            
            Console.WriteLine($"Deposit count: {++count}"); // вывод порядкового номера вклада
            Console.WriteLine(deposit.ToString()); // вывод инфо об объекте   
        }
    }
        
}