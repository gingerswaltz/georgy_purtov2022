﻿class MyProg
{
    static bool IsPalindrom(string str)
{
    if (str == null) throw new ArgumentNullException("str");
    str = str.ToLower().Replace(" ", string.Empty);
    return IsPalindromInternal(str);
}


static bool IsPalindromInternal(string str)
{
    if (str.Length == 1 || string.IsNullOrEmpty(str)) return true;
    if (!str[0].Equals(str[str.Length - 1])) return false;
    return IsPalindromInternal(str.Substring(1, str.Length - 2));
}

static void Main(string[] args)
{


        string str, str2="";
        int _i,j;
        Console.WriteLine("Input string");
        str = Console.ReadLine();
        
        Console.WriteLine("Input j");

        Int32.TryParse(Console.ReadLine(), out j);
        
        
        Console.WriteLine("Input i");

        int.TryParse(Console.ReadLine(), out _i);


        for (int i=_i-1;  i <j; i++)
        {
            str2 += str[i];
        }

    Console.WriteLine(IsPalindrom(str2));
}
}
