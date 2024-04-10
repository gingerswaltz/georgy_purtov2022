class FSM:
    def __init__(self, initial_state):
        self.initial_state = initial_state
        self.current_state = initial_state
        self.states = {}

    def set_initial_state(self, initial_state):
        self.initial_state = initial_state
        self.current_state = initial_state

    def add_state(self, state, transitions):
        self.states[state] = transitions

    def process(self, symbol):
        if self.current_state not in self.states:
            raise Exception("Invalid current state")

        transitions = self.states[self.current_state]
        if symbol in transitions:
            action = transitions[symbol].get("action")
            if action:
                action()

            next_state = transitions[symbol].get("next")
            if next_state:
                self.current_state = next_state
        elif "*" in transitions:
            default_action = transitions["*"].get("action")
            if default_action:
                default_action()

            default_next_state = transitions["*"].get("next")
            if default_next_state:
                self.current_state = default_next_state
        else:
            raise Exception("Unrecognized symbol")


class ChatBot(FSM):
    def __init__(self):
        super().__init__("INIT")
        self.session = {}
        self.login = ""

        self.add_state("INIT", {
            "*": {"action": self.do_introduce, "next": "INIT"},
            "LOGIN": {"action": self.do_login, "next": "SESSION"},
            "EXIT": {"action": self.do_quit, "next": "INIT"}
        })

        self.add_state("SESSION", {
            "SAY": {"action": self.do_say, "next": "SESSION"},
            "*": {"next": "SESSION"},
            "MEMORIZE": {"next": "STORE"},
            "EXIT": {"next": "INIT"}
        })

        self.add_state("STORE", {
            "*": {"action": self.do_remember, "next": "STORE"},
            "EXIT": {"next": "SESSION"}
        })

    def normalize(self, symbol):
        if symbol.strip():
            parts = symbol.split(" ", 1)
            return parts[0].upper(), parts[1] if len(parts) > 1 else ""
        return "*", ""

    def do_introduce(self):
        print("Please introduce yourself first!")

    def do_login(self):
        self.login = input("Enter your name: ")
        print("Welcome, " + self.login)
        self.session.setdefault(self.login, [])

    def do_say(self):
        data = self.session.get(self.login)
        if data:
            print(data)
        else:
            print("No record")

    def do_remember(self):
        message = input("Enter your message: ")
        self.session.setdefault(self.login, []).append(message)

    def do_quit(self):
        print("Bye bye!")
        exit()


if __name__ == "__main__":
    bot = ChatBot()
    while True:
        user_input = input().strip()
        if not user_input:
            continue

        symbol, data = bot.normalize(user_input)
        bot.process(symbol)
