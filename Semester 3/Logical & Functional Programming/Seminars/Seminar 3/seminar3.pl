% Given a list of numbers and sublists of numbers,
% substitute each of sublist in which the sum of the elems is odd with the first elem of that sublist.
% ex: [1,2,[2,4],7,3,[4,4,7],[1],8,10,[2,3]] =>[1,2,[2,4],7,3,4,1,8,10,2]

%sum(L, S).
(i,o) ; (i,i) flow
sum([],0).
sum([H|T], NewS):-
	sum(T,S),
	NewS is S+H.

% mathematically: solve(L(1...n)) = [], if n=0
% 				= L1 U solve(L(2...n)), if L1 is list and sum(L1) is odd
% 				= L U solve(L(2...n))

solve([],[]).
solve([H|T], [NewH|NewT]):-
	isList(H),
	sum(H,S),
	S % 2 =:= 1, !, %if the sum is odd than do not return to the instructions above
	H = [NewH | _], %concatenate to the result list
	solve(T,NewT).
solve([H|T],[H|NewT]):-
	solve(T,NewT).
	
	



% Given a list of numbers and sublists of numbers,
% remove the odd numbers from the sublists that have a mountain aspect.
% math: remove_odd(L[1...n]) = [] if n=0
% 			   = L1 U remove_odd(L[2...n]) if L1 is even
% 			   = remove_odd(L[2...n]) if L1 odd

odd(E):- mod(E,2) =:= 1.

remove_odd([],[]).
remove_odd([H|T],R):-
	\+ odd(H), !,
	remove_odd(T,R1).
	R1 = [H|R1].
remove_odd([H|T], R):-
	remove_odd(T,R).

% math: mountain(L[1...n], b) = true if n=1 and b=1
% 			    = mountain(L[2...n],1) if L1 > L2 and (b=1 or b=1) %decreasing
% 			    = mountain(L[2...n],0) if L1 < L2 and b=0 %for checking if it is increasing using flag b
% 			    = false, otherwise

main_mountain([H1,H2|T]):-
	H1 < H2,
	mountain()[H1,H2|T],0).

mountain([_],1).
mountain([H1,H2|T],_):- %_ bc b can be either 0 or 1
	H1 > H2,
	mountain([H1,H2|T],1).
mountain([H1,H2|T],0):-
	H1 < H2,
	mountain([H2|T],0).


% math: solve(L[1...n]) = [] if n = 0
% 		      = remove_odd(L1) U solve(L[2...n]) if isList(L1) and mountain(L1)
% 		      = L1 U solve(L[2...n]) otherwise

solve([],[]). %flow model (i,o)
solve([H|T],R):-
	isList(H),
	main_mountain(H), !,
	remove_odd(H, RR),
	solve(T,0),
	R = [RR|0].
solve([H|T],[H|RR]):-
	solve(T,RR).





% DISCUSSION - PERMUTATIONS OF A LIST:
perm(L[1...n]) = insert(L1, perm(L[2...n]))
	       = [] if n=0
insert(e, L[1...n]) = e U L[1...n] if n>0
		    = e U insert(e, L[2...n]), if n>0
		    = [e] if n=0
	
	