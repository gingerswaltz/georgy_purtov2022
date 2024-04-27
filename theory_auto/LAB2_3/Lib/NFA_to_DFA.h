#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

// ������� ����������
vector<vector<string>> transition_table; // ������� ��������� ���
vector<string> states; // ��������� ���
vector<string> alphabets; // ������� ���
string start_state; // ��������� ��������� ���

// �������� ����������
vector<pair<string, vector<string>>> dfa_table; // ������� ��������� ���
vector<pair<string, bool>> completed; // ����� ���������� ��������� ���

// ��������� �������
void take_input();
void print_output();
void create_state_transitions(string state);
string unite(vector<string> store_state);
string fetch(char c, int alphabet);
bool isCompleted(string state);
void print_dfa();

//int main() {
//    setlocale(LC_ALL, "RU");
//    take_input();
//    print_output();
//    create_state_transitions(start_state);
//    print_dfa();
//    return 0;
//}

//���������� ������� ������ 
void take_input() {
    int number_of_states, number_of_alphabets;
    string state;

    cout << "���������� ���������: ";
    cin >> number_of_states;
    cout << "������� ���������: ";
    for (int i = 0; i < number_of_states; i++) {
        cin >> state;
        states.push_back(state);
    }

    cout << "���������� �������� ��������: ";
    cin >> number_of_alphabets;
    cout << "������� ������� ��������: ";
    string alphabet;
    for (int i = 0; i < number_of_alphabets; i++) {
        cin >> alphabet;
        alphabets.push_back(alphabet);
    }

    cout << "������� ������� ��������� ��� (��� �������!):\n";
    for (int i = 0; i < states.size(); i++) {
        vector<string> row_states;
        for (int j = 0; j < alphabets.size(); j++) {
            cin >> state;
            row_states.push_back(state);
        }
        transition_table.push_back(row_states);
    }

    cout << "������� ��������� ���������: ";
    cin >> start_state;
}

void take_input_static() {
    int number_of_states = 4, number_of_alphabets = 2;
    string state;
    cout << "���������� ���������: 4 " << endl;
    states.push_back("S");
    states.push_back("A");
    states.push_back("B");
    states.push_back("H");

    cout << "���������� �������� ��������: 2 "<< endl;
    string alphabet;
    alphabets.push_back("0");
    alphabets.push_back("1");


    vector<string> row_statesS;
    row_statesS.push_back("NULL");
    row_statesS.push_back("NULL");
    transition_table.push_back(row_statesS);
    
    vector<string> row_statesA;
    row_statesA.push_back("SB");
    row_statesA.push_back("SA");
    transition_table.push_back(row_statesA);

    vector<string> row_statesB;
    row_statesB.push_back("NULL");
    row_statesB.push_back("SA");
    transition_table.push_back(row_statesB);

    vector<string> row_statesH;
    row_statesH.push_back("S");
    row_statesH.push_back("SA");
    transition_table.push_back(row_statesH);

               
    start_state = "H";
}
//����� ������� ������
void print_output() {
    cout << "���������: ";
    for (int i = 0; i < states.size(); i++) cout << states[i] << " ";
    cout << endl;
    cout << "�������: ";
    for (int i = 0; i < alphabets.size(); i++) cout << alphabets[i] << " ";
    cout << endl;

    cout << "������� ���������:\n";
    cout << "\t   0 \t 1\n";
    for (int i = 0; i < states.size(); i++) {
        cout << states[i] << "\t: ";
        for (int j = 0; j < alphabets.size(); j++) {
            cout << transition_table[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "��������� ���������: " << start_state;
    cout << endl;
}
//��������, ���� �� ��������� ��� ���������� � ��������� � ������� ��������� ���
bool isCompleted(string state) {
    for (int i = 0; i < completed.size(); i++) {
        if (completed[i].first == state) return completed[i].second;
    }
    return false; // ��������� ��� �� �������.
}
// ��������� ������ �������� � ����� �������� � ���������� ���������, 
// � ������� ���������� ������� �� ������� ��������� �� ������� �������
string fetch(char c, int alphabet) {
    string s(1, c);
    int state_index = 0;
    for (int i = 0; i < states.size(); i++)
        if (states[i] == s) {
            state_index = i;
            break;
        }

    return transition_table[state_index][alphabet];
}
//��������� ������ ��������� � ���������� �� � ���� ���������. 
// ��� ������� ������������� ������� � ���������� ����� ���������.
string unite(vector<string> store_state) {
    // ��������� ���� ������������ ��������� �� �������
    set<char> split_s;
    for (int i = 0; i < store_state.size(); i++) {
        if (store_state[i] == "NULL") continue;
        for (int j = 0; j < store_state[i].size(); j++) {
            split_s.insert(store_state[i][j]);
        }
    }

    // ������������ ������ ���������
    string new_state = "";
    for (auto element : split_s) new_state += element;
    return new_state;
}

//���������� ������� ������� ��������� ���. 
// ��� ��������� ��������� � �������� ��������� � ���������,
//  ���� �� ��� ��� ����������.
//  ���� ���, �� ������� ����� ������ � ������� ��������� ���.
void create_state_transitions(string state) {
    if (isCompleted(state))return;

    vector<string> dfa_row;
    for (int a = 0; a < alphabets.size(); a++) {
        vector<string>store_state;
        // ��� ������� ������� �������� ������� �������� fetch() 
        // ��� ������� ��������� � ��������� ��������� � ������ store_state.
        for (int w = 0; w < state.size(); w++) {
            store_state.push_back(fetch(state[w], a));
        }
        //���������� ������� unite() ��� ������� store_state, ����� �������� ����� ������������ ���������.
        string new_state = unite(store_state);

        dfa_row.push_back(new_state);
    }
    //����� ������ ������� ��������� ��� ����������� � ������ dfa_table
    dfa_table.push_back(make_pair(state, dfa_row));
    //��������� ���������� ��� �����������, ����� �������� ��������� ���������.
    completed.push_back(make_pair(state, true));

    //���������� ���������� create_state_transitions() ��� ������� ������ ��������� � ������ ������� ��������� ���, ���� ��� �� �������� "NULL"
    for (int i = 0; i < dfa_row.size(); i++)
        if (dfa_row[i] != "NULL")
            create_state_transitions(dfa_row[i]);
}

//����� ������� ��������� ���
void print_dfa() {
    cout << "������� ��������� ��� :\n";
    cout << "\t 0 \t 1\n";
    for (int i = 0; i < dfa_table.size(); i++) {
        cout << dfa_table[i].first << "\t:";
        for (int j = 0; j < dfa_table[i].second.size(); j++) {
            cout << dfa_table[i].second[j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}