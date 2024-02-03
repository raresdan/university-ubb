% Se da o lista L de numere si de atomi.
% a) Sa se stearga toti atomi si toate elementele de valoare impara din lista si sa se determine cmmdc al acestei liste.
% b) Sa se dubleze elementele ramase in lista.
% L = [ a, m, 10, 5, 6, 2, 3, 12, 2, n, z ]
% a) NL = [10, 6, 2, 12, 2]
% b) NL = [10, 10, 6, 6, 2, 2, 12, 12, 2, 2]

only_even([], []).
only_even([H|T], Result) :- 
    number(H), 
    mod(H, 2) =:= 0, 
    only_even(T, TempResult),
    Result = [H|TempResult].
only_even([_|T], Result) :-
    only_even(T, Result).

double_numbers([], []).
double_numbers([H|T], Result) :-
    double_numbers(T, TempResult),
    Result = [H, H|TempResult].


main2(List, Result):-
    only_even(List, TempResult),
    double_numbers(TempResult, Result).