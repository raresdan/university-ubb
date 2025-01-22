import json
from dataclasses import dataclass
from typing import List, Set

from finiteAutomataData import FiniteAutomataData
from transition import Transition


class FiniteAutomata:
    def __init__(self, file_path: str):
        with open(file_path, 'r') as file:
            data = json.load(file)

        fa_data = FiniteAutomataData(
            states=data['states'],
            initial_state=data['initial_state'],
            final_states=data['final_states'],
            alphabet=data['alphabet'],
            transitions=[Transition(t['from'], t['to'], t['on']) for t in data['transitions']]
        )

        self.states: Set[str] = set(fa_data.states)
        self.initial_state: str = fa_data.initial_state
        self.final_states: Set[str] = set(fa_data.final_states)
        self.alphabet: Set[str] = set(fa_data.alphabet)
        self.transitions: List[Transition] = fa_data.transitions

    @staticmethod
    def menu():
        print("1. States")
        print("2. Initial States")
        print("3. Final States")
        print("4. Alphabet")
        print("5. Transitions")
        print("6. Check sequence")
        print("7. Check if deterministic")
        print("0. Exit")

    def choice(self):
        try:
            x = int(input(">> "))
        except Exception:
            print("Invalid number")
            return -1

        return x

    def display(self):
        self.menu()
        x = self.choice()
        if x == 0:
            return -1
        elif x == 1:
            print("States:", ", ".join(self.states))
            return 0
        elif x == 2:
            print("Initial State:", self.initial_state)
            return 0
        elif x == 3:
            print("Final States:", ", ".join(self.final_states))
            return 0
        elif x == 4:
            print("Alphabet:", ", ".join(self.alphabet))
            return 0
        elif x == 5:
            print("Transitions:")
            for transition in self.transitions:
                print(f"\t{transition.from_} --{transition.on}--> {transition.to}")
            return 0
        elif x == 6:
            print("\nEnter a sequence to check if it is accepted by the finite automata:")
            sequence = input(">> ")
            if self.is_accepted(sequence):
                print("Accepted by the finite automata.")
            else:
                print("NOT accepted by the finite automata.")
        elif x == 7:
            result = self.is_deterministic()
            if result:
                print("The finite automata is deterministic.")
            else:
                print("The finite automata is NOT deterministic.")
        else:
            return 0


    def is_accepted(self, sequence: str) -> bool:
        current_state = self.initial_state
        for symbol in sequence:
            symbol_string = str(symbol)
            transition = next((t for t in self.transitions if t.from_ == current_state and t.on == symbol_string), None)
            if transition:
                current_state = transition.to
            else:
                return False
            
        return current_state in self.final_states
    
    def is_deterministic(self) -> bool:
        transition_dict = {}
        for transition in self.transitions:
            if transition.on == 'ε':
                return False
            key = (transition.from_, transition.on)
            if key in transition_dict:
                return False
            transition_dict[key] = transition.to
        return True

