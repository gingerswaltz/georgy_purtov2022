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

        # Do some action
        if callable(state[symbol]['ACTION']):
            state[symbol]['ACTION'](self, raw_symbol)

        # Switch state
        if symbol in state and 'NEXT' in state[symbol]:
            self.CURRENT = state[symbol]['NEXT']
        else:
            raise Exception("Don't know how to handle symbol {}".format(raw_symbol['SYMBOL']))
