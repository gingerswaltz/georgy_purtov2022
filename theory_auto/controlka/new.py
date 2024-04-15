class FSM:
    def __init__(self, initial_state):
        # Инициализация объекта конечного автомата с начальным состоянием
        self.initial_state = initial_state
        self.current_state = initial_state
        self.states = {}

    def set_initial_state(self, initial_state):
        # Метод для установки начального состояния
        self.initial_state = initial_state
        self.current_state = initial_state

    def add_state(self, state, transitions):
        # Метод для добавления состояния и его переходов
        self.states[state] = transitions

    def process(self, symbol):
        # Метод для обработки символа в текущем состоянии
        if self.current_state not in self.states:
            raise Exception("Invalid current state")

        transitions = self.states[self.current_state]
        if symbol in transitions:
            # Если символ имеет переход в текущем состоянии, выполняем соответствующее действие
            action = transitions[symbol].get("action")
            if action:
                action()

            # Переходим в следующее состояние, если оно указано
            next_state = transitions[symbol].get("next")
            if next_state:
                self.current_state = next_state
        elif "*" in transitions:
            # Если символ не имеет явного перехода, но есть общий переход "*", выполняем его
            default_action = transitions["*"].get("action")
            if default_action:
                default_action()

            default_next_state = transitions["*"].get("next")
            if default_next_state:
                self.current_state = default_next_state
        else:
            # Если символ не определен в текущем состоянии, возбуждаем исключение
            raise Exception("Unrecognized symbol")

        # Добавляем запрос на ввод сообщения после команды MEMORIZE
        if symbol == "MEMORIZE":
            self.do_remember()

class ChatBot(FSM):
    def __init__(self):
        # Инициализация чат-бота как объекта конечного автомата
        super().__init__("INIT")
        self.session = {}
        self.login = ""

        # Определение переходов и действий для различных состояний чат-бота
        self.add_state("INIT", {
            "*": {"action": self.do_introduce, "next": "INIT"},
            "LOGIN": {"action": self.do_login, "next": "SESSION"},
            "EXIT": {"action": self.do_quit, "next": "INIT"},
            "HELP": {"action": self.do_help, "next": "INIT"}  # Добавляем переход для команды HELP
        })

        self.add_state("SESSION", {
            "SAY": {"action": self.do_say, "next": "SESSION"},
            "*": {"next": "SESSION"},
            "MEMORIZE": {"action": self.do_remember, "next": "STORE"},
            "EXIT": {"next": "INIT"},
            "HELP": {"action": self.do_help, "next": "SESSION"}  # Добавляем переход для команды HELP
        })

        self.add_state("STORE", {
            "*": {"action": self.do_remember, "next": "STORE"},
            "EXIT": {"next": "SESSION"},
            "HELP": {"action": self.do_help, "next": "STORE"}  # Добавляем переход для команды HELP
        })
        
    def normalize(self, symbol):
        # Метод для нормализации символа, приведения его к верхнему регистру и разделению на части
        if symbol.strip():
            parts = symbol.split(" ", 1)
            return parts[0].upper(), parts[1] if len(parts) > 1 else ""
        return "*", ""

    def do_introduce(self):
        # Действие для представления чат-бота при начале сеанса
        print("Представьтесь пожалуйста!")

    def do_login(self):
        # Действие для ввода имени пользователя и приветствия
        self.login = input("Введите имя: ")
        print("Привет, " + self.login)
        self.session.setdefault(self.login, [])

    def do_say(self):
        # Действие для вывода сообщений пользователя
        messages = self.session.get(self.login, [])
        if messages:
            for message in messages:
                print(message)
        else:
            print("Нет истории")

    def do_remember(self):
        # Действие для запоминания сообщений пользователя
        message = input("Введите сообщение: ")
        self.session.setdefault(self.login, []).append(message)

    def do_quit(self):
        # Действие для завершения работы чат-бота
        print("Bye bye!")
        exit()

    def do_help(self):
        # Действие для вывода помощи пользователю
        print("Справка:")
        print("- LOGIN: вход в систему")
        print("- SAY: просмотр истории ваших сообщений")
        print("- MEMORIZE: запомнить ваше сообщение")
        print("- EXIT: выйти из бота")
        print("- HELP: просмотр справки")



if __name__ == "__main__":
    bot = ChatBot()
    while True:
        user_input = input().strip()
        
        # Если пользователь ввел только "MEMORIZE", то нам не нужно обрабатывать пустой ввод
        if user_input.upper() == "MEMORIZE":
            symbol = user_input.upper()
        else:
            symbol, data = bot.normalize(user_input)

        bot.process(symbol)
