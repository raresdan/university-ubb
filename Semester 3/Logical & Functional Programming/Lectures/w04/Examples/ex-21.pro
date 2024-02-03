% A heterogeneous list of numbers, symbols and / or lists of numbers is given.
% Determine the sum of the numbers in the heterogeneous list.

% ?- sum([1, a, [1,2,3], 4], S).
% S = 11.
%
% ?- sum([a, b, []], S).
% S = 0.

% sumalist(L: list of numbers, S: number)
% (i, o) - deterministic

sumalist([], 0).

sumalist([H | T], S) :-
  sumalist(T, S1),
  S is S1 + H.

% sum(L: list, S: number)
% (i, o) - deterministic

sum([], 0).

sum([H | T], S) :-
  number(H),
  !,
  sum(T, S1),
  S is H + S1.

sum ([H | T], S) :-
  is_list(H),
  !,
  sumalist(H, S1),
  sum(T, S2),
  S is S1 + S2.

sum([_ | T], S) :-
  sum(T, S).
