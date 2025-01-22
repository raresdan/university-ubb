from finiteAutomata import FiniteAutomata

file_path_fa = "FA.in"

finite_automata = FiniteAutomata(file_path_fa)
stop = 0

while stop != -1:    
    stop = finite_automata.display()
