%mulk(L - list, K - number, R - result list)
%flow model(i,i,o)
mulk([],_,[]).
mulk([H|T], K, R):-
    NewH is H*K,
    mulk(T, K, TR),
    R=[NewH|TR].

%sumC(L-list, C-collector, S-result)
%flow model (i,i,o)
sumC([], C, C).
sumC([H|T], C, R):-
    NewC is C+H,
    sumC(T, NewC, R).

%suma(L-list, S-return number)
%flow model (i,o) (i,i)
suma([],0).
suma([H|T], S):-
    suma(T, TS),
    S is H+TS.