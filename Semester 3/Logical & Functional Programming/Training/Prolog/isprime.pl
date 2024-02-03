% is prime function

divisible(X,Y) :- 
    0 is X mod Y, 
    !.
divisible(X,Y) :- 
    X > Y+1, 
    divisible(X, Y+1).

is_prime(2):-
    true,!.
is_prime(X):-
    X < 2,
    !,
    false.
is_prime(X):-
    \+ divisible(X, 2).
