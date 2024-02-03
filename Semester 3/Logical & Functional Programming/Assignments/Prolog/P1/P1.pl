% 4.
% a. Write a predicate to determine the difference of two sets.
% b. Write a predicate to add value 1 after every even element from a list.

% difference(+List, +List, -Result)
difference([], _, []).
difference([X|A], B, Difference) :-
    member(X, B), 		%verify if X is in B
    !,					%if yes we skip it
    difference(A, B, Difference).
difference([X|A], B, [X|Difference]) :-
    difference(A, B, Difference).



% add_one_to_even(+List, -Result)
add_one_to_even([], []).
add_one_to_even([X|Rest], [X, 1|Result]) :-
    0 is X mod 2,		%if X even, add X and also 1 to the result
    add_one_to_even(Rest, Result).
add_one_to_even([X|Rest], [X|Result]) :-
    X mod 2 =\= 0,		%if X odd, just add itself
    add_one_to_even(Rest, Result).