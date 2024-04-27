#include <iostream>
#include "../Lib/NFA_to_DFA.h"
#include "../Lib/FormalLanguage.h"
#include "../Lib/Rule.h"

using namespace std;

enum State { H, BCS, BS, B, ER};// ER состояние ошибки

void Analizator(const string& text) {
    State now = H;
    int count = 0;
    string res = "";
    bool reachedFinalState = false;//флаг проверки последнего состояния
    do {
        // Проверка выхода за пределы индексации
        if (count < text.length()) {
            switch (now) {
            case H: {
                if (text[count] == '0')
                    now = BS;
                else if (text[count] == '1')
                    now = B;
                else
                    now = ER;
                break;
            }
            case BS: {
                if (text[count] == '0')
                    now = BCS;
                else
                    now = ER;
                break;
            }
            case BCS: {
                if (text[count] == '0')
                    now = BCS;
                else if (text[count] == '1')
                    now = B;
                else
                    now = ER;
                break;
            }
            case B: {
                if (text[count] == '0')
                    now = BCS;
                else
                    now = ER;
                break;
            }
            default:
                break;
            }

            res += to_string(now) + " ";
            count++;
        }
        else
            break;
    }// while (now != S && text[count] != '\u00A7');
    while (now != ER && text[count] != '\u00A7'); //now != State.S &&
    cout << res << endl;

}

int main()
{
    setlocale(LC_ALL, "RU");

    cout << "Задание 2.3" << endl;
    list<Rule> dict =
    {
       Rule("B", "B0"),
       Rule("B", "S0"),
       Rule("B", "C0"),
       Rule("H", "B1"),
       Rule("H", "B0"),
       Rule("H", "S0"),
       Rule("C", "B1")
    };

    PrintRules(dict);
    FormalLanguage fl(dict);

    take_input();
    //take_input_static();
    print_output();
    create_state_transitions(start_state);
    print_dfa();



    cout << "Анализаторы цепочек " << endl;
    cout << "Состояния: H-0, BS-1, BCS-2, B-3, ER-4" << endl;
    cout << "Цепочка 1011    \t:";
    Analizator("1011");
    cout << "Цепочка 0       \t:";
    Analizator("0");
    cout << "Цепочка 101011  \t:";
    Analizator("101011");
    cout << endl;

    cout << "G ({0,1}, {H, S, BCS, BS, B},P,H)" << endl;

    return 0;
}
