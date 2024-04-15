import tkinter as tk
from tkinter import messagebox

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
        self.output = ""

        self.add_state("INIT", {
            "*": {"action": self.do_introduce, "next": "INIT"},
            "LOGIN": {"action": self.do_login, "next": "SESSION"},
            "EXIT": {"action": self.do_quit, "next": "INIT"}
        })

        self.add_state("SESSION", {
            "SAY": {"action": self.do_say, "next": "SESSION"},
            "*": {"next": "SESSION"},
            "MEMORIZE": {"action": self.do_remember, "next": "STORE"},
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
        self.output = "Please introduce yourself first!"

    def do_login(self, user_input):
        self.login = user_input.strip()
        self.output = "Welcome, " + self.login
        self.session.setdefault(self.login, [])

    def do_say(self):
        messages = self.session.get(self.login, [])
        if messages:
            self.output = "\n".join(messages)
        else:
            self.output = "No record"

    def do_remember(self, user_input):
        message = user_input.strip()
        self.session.setdefault(self.login, []).append(message)

    def do_quit(self):
        self.output = "Bye bye!"
        app.destroy()

class ChatBotGUI:
    def __init__(self, master):
        self.master = master
        self.master.title("ChatBot")

        self.bot = ChatBot()

        self.initialize_ui()

    def initialize_ui(self):
        self.label = tk.Label(self.master, text="Enter command:")
        self.label.pack()

        self.entry = tk.Entry(self.master)
        self.entry.pack()

        self.button = tk.Button(self.master, text="Send", command=self.send_command)
        self.button.pack()

        self.output_text = tk.Text(self.master, height=10, width=50)
        self.output_text.pack()

    def send_command(self):
        user_input = self.entry.get().strip()
        symbol, data = self.bot.normalize(user_input)
        try:
            if symbol in ["LOGIN", "MEMORIZE"]:
                getattr(self.bot, f"do_{symbol.lower()}")(user_input)
            else:
                self.bot.process(symbol)
            self.update_output()
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def update_output(self):
        self.output_text.delete(1.0, tk.END)
        self.output_text.insert(tk.END, self.bot.output)

if __name__ == "__main__":
    root = tk.Tk()
    app = ChatBotGUI(root)
    root.mainloop()
