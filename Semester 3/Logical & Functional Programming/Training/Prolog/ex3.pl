% Se da o lista L de numere intregi, pozitive si negative.
% a) Sa se creeze 2 liste N si P astfel: P va contine doar numerele pozitive, iar N va contine numerele negative.
% b) Determinati elementele minime din cele doua liste create.
% L = [2, 4, 9, -7, -6, 4, -5]
% a) N = [-7, -6, -5]
% P = [2, 4, 9, 4]
% b) Min_n = -7
% Min_p = 2

neagtives([], []).
neagtives([H|T], Result):-
    H < 0,
    neagtives(T, TempResult),
    Result = [H|TempResult].
neagtives([_|T], Result):-
    neagtives(T, Result).

positives([],[]).
positives([H|T], Result):-
    H >= 0,
    positives(T, TempResult),
    Result = [H|TempResult].
positives([_|T], Result):-
    positives(T, Result).

minimum([H|_], H).
minimum([H|T], MinVal):-
    H < MinVal,
    minimum(T, H).
minimum([_|T], MinVal):-
    minimum(T, MinVal).


main3(List, N, P, MinN, MinP):-
    neagtives(List, N),
    positives(List, P),
    minimum(N, MinN),
    minimum(P, MinP).