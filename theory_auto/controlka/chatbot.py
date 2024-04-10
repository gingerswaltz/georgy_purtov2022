class FSM:
    def __init__(self, initial):
        self.INITIAL = initial
        self.CURRENT = initial
        self.STATES = {}

    def set_initial_state(self, initial):
        self.INITIAL = initial

    def set_current_state(self, current):
        self.CURRENT = current

    def get_current_state(self):
        return self.CURRENT

    def reset(self):
        self.CURRENT = self.INITIAL

    def add_state(self, state, symbol, next_state, action):
        if state not in self.STATES:
            self.STATES[state] = {}
        self.STATES[state][symbol] = {'NEXT': next_state, 'ACTION': action}

    def remove_state(self, state, symbol=None):
        if symbol:
            del self.STATES[state][symbol]
        else:
            del self.STATES[state]

    def normalize(self, symbol):
        return {'SYMBOL': symbol}

    def process(self, raw_symbol):
        state = self.STATES[self.CURRENT]
        raw_symbol = self.normalize(raw_symbol)
        symbol = raw_symbol['SYMBOL']

        print("Current state {}, got symbol {}".format(self.CURRENT, symbol))
        if symbol not in state and '*' in state:
            print("Unrecognized symbol {}, using *".format(symbol))
            symbol = "*"

        # Do some action!
        if callable(state[symbol]['ACTION']):
            state[symbol]['ACTION'](self, raw_symbol)

        # Switch state
        if symbol in state and 'NEXT' in state[symbol]:
            self.CURRENT = state[symbol]['NEXT']
        else:
            raise Exception("Don't know how to handle symbol {}".format(raw_symbol['SYMBOL']))

        
class ChatBot(FSM):
    def __init__(self):
        super().__init__("INIT")
        self.add_state("INIT", "*", "INIT", self.do_introduce)
        self.add_state("INIT", "LOGIN", "SESSION", self.do_login)
        self.add_state("INIT", "EXIT", "INIT", self.do_quit)
        self.add_state("SESSION", "*", "SESSION", None)
        self.add_state("SESSION", "EXIT", "INIT", None)
        self.add_state("SESSION", "SAY", "SESSION", self.do_say)
        self.add_state("SESSION", "MEMORIZE", "STORE", None)
        self.add_state("STORE", "*", "STORE", self.do_remember)
        self.add_state("STORE", "EXIT", "SESSION", None)
        self.SESSION = {}
        self.LOGIN = ""

    def normalize(self, symbol):
        ret = {}
        if " " in symbol:
            symbol, data = symbol.split(" ", 1)
            ret['SYMBOL'] = symbol.upper()
            ret['DATA'] = data
            ret['RAW'] = symbol + " " + data
        else:
            ret['SYMBOL'] = "*"
            ret['DATA'] = symbol
            ret['RAW'] = symbol
        return ret

    def do_introduce(self, symbol):
        print("Please introduce yourself first!")
        return self

    def do_login(self, symbol):
        print("Welcome, {}".format(symbol['DATA']))
        self.LOGIN = symbol['DATA']
        if self.LOGIN not in self.SESSION:
            self.SESSION[self.LOGIN] = []
        return self

    def do_say(self, symbol):
        if self.LOGIN in self.SESSION and symbol['DATA'] < len(self.SESSION[self.LOGIN]):
            print(self.SESSION[self.LOGIN][symbol['DATA']])
        else:
            print("No record")
        return self

    def do_remember(self, symbol):
        if self.LOGIN in self.SESSION:
            self.SESSION[self.LOGIN].append(symbol['RAW'])
        return self

    def do_quit(self, symbol):
        print("Bye bye!")
        exit()

