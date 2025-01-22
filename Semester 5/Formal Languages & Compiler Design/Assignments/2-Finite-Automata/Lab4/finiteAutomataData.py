from dataclasses import dataclass
from typing import List
from transition import Transition

@dataclass
class FiniteAutomataData:
    states: List[str]
    initial_state: str
    final_states: List[str]
    alphabet: List[str]
    transitions: List[Transition]
