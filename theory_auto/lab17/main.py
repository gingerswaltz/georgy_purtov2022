import random

class Rule:
    def __init__(self, a, b, l=False):
        self.A = a
        self.B = b
        self.isLooped = l

def print_rules(rules):
    print("Правила для языка:")
    for rule in rules:
        print(rule.A, "->", rule.B)

class FormalLanguage:
    def __init__(self, rules, count=100):
        self.rules = rules
        self.MaxRepetitionsCount = count

    def check_loop(self, input_str, rule, count=10):
        for _ in range(count):
            A = rule.A
            B = rule.B
            pos = input_str.find(A)
            if pos != -1:
                input_str = input_str[:pos] + B + input_str[pos + len(A):]
            else:
                return False
        return True

    def refresh_rules(self):
        for rule in self.rules:
            rule.isLooped = False

    def translate(self, text):
        count = 0
        is_end = False
        while count < self.MaxRepetitionsCount:
            if is_end:
                break
            count += 1
            is_end = True
            for rule in self.rules:
                if not rule.isLooped:
                    A = rule.A
                    B = rule.B
                    pos = text.find(A)
                    if pos != -1:
                        if self.check_loop(text, rule):
                            rule.isLooped = True
                        else:
                            text = text[:pos] + B + text[pos + len(A):]
                            is_end = False
                            break
                else:
                    rule.isLooped = True
        self.refresh_rules()
        return text

    def output_left(self):
        result = "S"
        count = 0
        while count < self.MaxRepetitionsCount:
            pos = float('inf')
            for rule in self.rules:
                key = rule.A
                find_pos = result.find(key)
                if (pos > find_pos or pos == float('inf')) and find_pos != -1:
                    pos = find_pos
            if pos == float('inf'):
                break
            rules_ = [rule for rule in self.rules if pos == result.find(rule.A)]
            index = random.randint(0, len(rules_) - 1)
            r = rules_[index]
            p = result.find(r.A)
            result = result[:p] + r.B + result[p + len(r.A):]
            count += 1
        return result

    def output_left_equivalence(self):
        result = "S"
        count = 0
        while count < self.MaxRepetitionsCount:
            pos = float('inf')
            for rule in self.rules:
                key = rule.A
                find_pos = result.find(key)
                if (pos > find_pos or pos == float('inf')) and find_pos != -1:
                    pos = find_pos
            if pos == float('inf'):
                break
            rules_ = [rule for rule in self.rules if pos == result.find(rule.A)]
            index = random.randint(0, len(rules_) - 1)
            r = rules_[index]
            p = result.find(r.A)
            result = result[:p] + r.B + result[p + len(r.A):]
            count += 1
        return result

    def transformations(self, chain_):
        buf = ""
        result = ""
        transformations = []
        found = False
        counter = 0
        while not found:
            buf = self.output_left()
            counter += 1
            if counter == 10000000:
                return "Цепочка не построена. Попробуйте ещё раз\n"
            if buf == chain_:
                found = True
        for transformation in transformations:
            result += transformation + "\n"
        result = "Начальный символ: S\n" + result
        return result

def fill_vector_with_unique_chars(input_string, vector):
    for c in input_string:
        if c not in vector:
            vector.append(c)

def equivalence(fl1, fl2):
    alphabet1, alphabet2 = [], []
    buf1, buf2 = "", ""
    transformations = []
    for _ in range(10000):
        buf1 = fl1.output_left_equivalence()
        buf2 = fl2.output_left_equivalence()
        fill_vector_with_unique_chars(buf1, alphabet1)
        fill_vector_with_unique_chars(buf2, alphabet2)
    alphabet1.sort()
    alphabet2.sort()
    print("\nСимволы в первом языке:", alphabet1)
    print("Символы во втором языке:", alphabet2)
    if alphabet1 == alphabet2:
        return "Грамматики эквивалентны"
    else:
        return "Грамматики не эквивалентны"

class Grammar:
    def __init__(self, vn, vt, rules, s="S"):
        self.Nonterminal = vn
        self.Terminal = vt
        self.P = rules
        self.S = s

    def get_type_grammar(self):
        is_type_one = True
        is_type_two = True
        is_type_three = True

        is_each_term_pos_bigger = True
        is_each_term_pos_smaller = True

        for r in self.P:
            is_type_one &= len(r.A) <= len(r.B)

            for vt in self.Terminal:
                is_type_two &= vt not in r.A

            if is_each_term_pos_bigger or is_each_term_pos_smaller:
                terminal_positions = []
                non_terminal_positions = []
                for vn in self.Nonterminal:
                    temp = r.B.find(vn)
                    if temp != -1:
                        non_terminal_positions.append(temp)
                for vt in self.Terminal:
                    temp = r.B.find(vt)
                    if temp != -1:
                        terminal_positions.append(temp)
                for pos in terminal_positions:
                    for pos_non_term in non_terminal_positions:
                        is_each_term_pos_bigger &= pos > pos_non_term
                        is_each_term_pos_smaller &= pos < pos_non_term
                if not is_each_term_pos_bigger and not is_each_term_pos_smaller:
                    is_type_three = False

        res = "0"
        if is_type_one:
            res += " 1"
        if is_type_two:
            res += " 2"
        if is_type_three:
            res += " 3"
        return res

    def make_tree(self, text):
        max_count = 10000
        count = 0
        tree = [text]

        while count < max_count:
            for rule in self.P:
                key = rule.A
                value = rule.B

                pos = text.find(value)
                if pos != -1:
                    text = text[:pos] + key + text[pos + len(value):]

                    separator = "|"
                    for i in range(pos):
                        separator = " " + separator
                    tree.append(separator)
                    tree.append(text)
            count += 1

        for item in reversed(tree):
            print(item)
        return text



def enum_to_string(s):
    state_to_string = {
        'H': "H",
        'N': "N",
        'P': "P",
        'S': "S",
        'ER': "ER"
    }
    return state_to_string[s]

def enum_to_string_2(s):
    state_to_string = {
        'H_': "H",
        'A_': "A",
        'B_': "B",
        'S_': "S",
        'ER_': "ER"
    }
    return state_to_string[s]

def Analizator(text):
    class State:
        H = 'H'
        N = 'N'
        P = 'P'
        S = 'S'
        ER = 'ER'

    now = State.H
    count = 0
    res = ""
    while count < len(text):
        if now == State.H:
            if text[count] == '0' or text[count] == '1':
                now = State.N
            else:
                now = State.ER
        elif now == State.N:
            if text[count] == '0' or text[count] == '1':
                now = State.N
            elif text[count] == '.':
                now = State.P
            else:
                now = State.ER
        elif now == State.P:
            if text[count] == '0' or text[count] == '1':
                now = State.S
            else:
                now = State.ER
        elif now == State.S:
            if text[count] == '0' or text[count] == '1':
                now = State.S
            else:
                now = State.ER

        res += enum_to_string(now)
        res += ""
        count += 1

    print("Цепочка состояний:", res)

    if now == State.S:
        print("Цепочка", text, "принадлежит данному языку\n")
    else:
        print("Цепочка", text, "не принадлежит данному языку\n")

def Analizator_2(text):
    class State_2:
        H_ = 'H_'
        A_ = 'A_'
        B_ = 'B_'
        S_ = 'S_'
        ER_ = 'ER_'

    now = State_2.H_
    count = 0
    res = ""
    while count < len(text):
        if now == State_2.H_:
            if text[count] == '0' or text[count] == '1':
                now = State_2.A_
            else:
                now = State_2.ER_
        elif now == State_2.A_:
            if text[count] == '0' or text[count] == '1':
                now = State_2.A_
            elif text[count] == '|':
                now = State_2.S_
            elif text[count] in ['+', '-']:
                now = State_2.B_
            else:
                now = State_2.ER_
        elif now == State_2.B_:
            if text[count] == '0' or text[count] == '1':
                now = State_2.A_
            else:
                now = State_2.ER_
        elif now == State_2.S_:
            now = State_2.ER_

        res += enum_to_string_2(now)
        res += ""
        count += 1

    print("Цепочка состояний:", res)

    if now == State_2.S_:
        print("Цепочка", text, "принадлежит данному языку\n")
    else:
        print("Цепочка", text, "не принадлежит данному языку\n")


# Lab 2
print("Задание 1")
Analizator("11.010")
Analizator("0.1")
Analizator("01.")
Analizator("100")
print("Данная грамматика порождает язык L = { 0^n 1^m . | n, m >= 0 }\n")

print("Задание 2")
Analizator_2("1011|")
Analizator_2("10+011|")
Analizator_2("1-101+1|3")

print("Грамматика: G: ({ 0, 1, +, - , | }, { A, B, S }, P, S)")

dict = {
    Rule("S", "A|"),
    Rule("A", "A0"),
    Rule("A", "A1"),
    Rule("A", "0"),
    Rule("A", "1"),
    Rule("A", "B0"),
    Rule("A", "B1"),
    Rule("B", "A+"),
    Rule("B", "A-"),
};
print_rules(dict)
print("Данная грамматика порождает язык L = { 0^n, 1^m, +^k, -^t , | | n, m > 0, k, t >= 0 }\n")

# Lab 1
#Задание 7
print("Задание 7\n")
dict1 = [
    Rule("S", "A.A"),
    Rule("A", "B"),
    Rule("A", "BA"),
    Rule("B", "0"),
    Rule("B", "1")
]
print_rules(dict1)

fl12 = FormalLanguage(dict1)
print("Цепочка:", fl12.translate("S"))

dict2 = [
    Rule("S", "0.A"),
    Rule("A", "0A"),
    Rule("A", "1")
]
print_rules(dict2)
fl13 = FormalLanguage(dict2)
print("Цепочка:", fl13.translate("S"))

print("Результат эквивалентности:", equivalence(fl12, fl13))

# Задание 9
print("\nЗадание 9\n")
dict3 = [
    Rule("S", "aSbS"),
    Rule("S", "bSaS"),
    Rule("S", "E")
]
print_rules(dict3)
fl14 = FormalLanguage(dict3)
print("Цепочка:", fl14.translate("S"))

gr = Grammar(["S"], ["a", "b", "E"], dict3)
print(gr.make_tree("aEbaEbE"))

# Задание 11 (а)
print("\nЗадание 11 (а)\n")
dict4 = [
    Rule("S", "0S"),
    Rule("S", "0B"),
    Rule("B", "1B"),
    Rule("B", "1C"),
    Rule("C", "1C"),
    Rule("C", "_|_")
]
print_rules(dict4)
print("Язык: L = { 0^n 1^m _|_ | n, m > 0}")

dict5 = [
    Rule("S", "A_|_"),
    Rule("A", "A1"),
    Rule("A", "B1"),
    Rule("B", "C1"),
    Rule("B", "CB1"),
    Rule("C", "0")
]
print_rules(dict5)
print("Язык: L = { 0^n 1^m _|_ | n, m > 0}")

# Задание 11 (б)
print("\nЗадание 11 (б)\n")
dict6 = [
    Rule("S", "aA"),
    Rule("S", "aB"),
    Rule("S", "bA"),
    Rule("A", "bS"),
    Rule("B", "aS"),
    Rule("B", "bB"),
    Rule("B", "_|_")
]
print_rules(dict6)
print("Язык: L = { a^n b^m _|_ | n, m > 0}")

dict7 = [
    Rule("S", "A_|_"),
    Rule("A", "ABb"),
    Rule("A", "Bb"),
    Rule("A", "Aa"),
    Rule("B", "a"),
    Rule("B", "b")
]
print_rules(dict7)
print("Язык: L = { a^n b^m _|_ | n, m > 0}")

# Задание 12
print("\nЗадание 12\n")
dict8 = [
    Rule("S", "S1"),
    Rule("S", "A0"),
    Rule("A", "A1"),
    Rule("A", "0"),
]
print_rules(dict8)
print("Язык: L = { 0 (1)^n 0 (1)^m  | n, m >= 0 }")

dict9 = [
    Rule("S", "A1"),
    Rule("S", "B0"),
    Rule("S", "E1"),
    Rule("A", "S1"),
    Rule("B", "C1"),
    Rule("B", "D1"),
    Rule("C", "0"),
    Rule("D", "B1"),
    Rule("E", "E0"),
    Rule("E", "1"),
]
print_rules(dict9)
print("Язык: L = { 0^n 1^m | n, m >= 0 }")

dict10 = [
    Rule("S", "S1"),
    Rule("S", "A0"),
    Rule("A", "A1"),
    Rule("A", "0"),
]
print_rules(dict10)
print("Язык: L = { 0 (1)^n 0 (1)^m  | n, m >= 0 }")