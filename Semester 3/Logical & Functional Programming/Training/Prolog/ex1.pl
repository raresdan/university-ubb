% Se da o lista neliniara formata din numere si atomi.
% Sa se determine, in ordine inversa, toate elementele nenumerice unice din lista data.
% L= (3 a (b (c (4 (d 5) b 3)) 7)) => R = (b d c a)

non_numeric([], []).
non_numeric([H|List], Result):-
    is_list(H),
    non_numeric(H, TempResult),
    non_numeric(List, TempResult2),
    append(TempResult, TempResult2, Result).
non_numeric([H|List], Result):-
    \+ number(H),
    non_numeric(List, TempResult),
    append(TempResult, [H], Result).
non_numeric([H|List], Result):-
    number(H),
    non_numeric(List, Result).

main1(List, Result):-
    non_numeric(List, NonNumeric),
    list_to_set(NonNumeric, Result).
    