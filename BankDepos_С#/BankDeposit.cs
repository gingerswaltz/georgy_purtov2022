namespace BankDeposit;
using System;


public class BankDeposit // основной класс
{
    public static void Main(string[] args) 
    {
        int i = 0;
        uint x = 1; // for int value
        double y = 1.0; // for float value
        string s; // для считывания символа отказа или согласия дальше
        char c;
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

                Console.WriteLine("Enter procents: up to 10% ");  // ввод процентов
                y = Convert.ToDouble(Console.ReadLine());
                depos1.setProc(y);

                Console.WriteLine("Enter amount of cash: "); // ввод денег
                y = Convert.ToDouble(Console.ReadLine());
                depos1.setMoney(y);

                Deposit.Add(depos1); // вставить новый объект в список 
            }

            while (true)
            {
                Console.WriteLine("Change amount of deposit? Type any key to accept or n to cancel");
                s= Console.ReadLine();
                if (s != "n" && s.ToLower() != "n")
                {
                    Console.WriteLine($"There are {Deposit.Count} deposites");
                    Console.WriteLine("Type number of deposit: ");

                    bool isNumber = int.TryParse(Console.ReadLine(), out i);
                    if (isNumber)
                    {
                        Console.Write("Current amount of deposit: ");
                        Console.WriteLine(Deposit[i-1].getMoney());
                        Console.Write("Type value of change: ");
                        y = Convert.ToDouble(Console.ReadLine());
                        Deposit[i - 1].MoneyChange(y);
                        Console.WriteLine();
                        Console.Write("Current amount of deposit: ");
                        Console.WriteLine(Deposit[i - 1].getMoney());
                    }
                   
                }
                else
                { break; }
            }



        }
        int count = 0; // счетчик
        foreach (BankDepos deposit in Deposit)  // цикл по элементам коллекции 
        {
            Console.WriteLine($"Deposit number: {++count}"); // вывод порядкового номера вклада
            Console.WriteLine(deposit.ToString()); // вывод инфо об объекте   
        }
    }
        
}