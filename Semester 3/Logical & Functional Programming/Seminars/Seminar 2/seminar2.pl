%Compute the number of occurences of an elem e in a list

occ([],_,0).
%list el no, flowmodel(i,i,o)
%                     (i,i,i)

occ([H|T], X, No):-
    H=x,
    !,
    occ(T,X,NewNo),
    No is NewNo + 1.

occ([H|T], X, No):-
    H\=X,
    occ(T,X,No).



%Implement a collector
%occ_collector(L:list, X:element, C:collector, R:result)
%flowmodel=(i,i,i,o)
%         =(i,i,i,i)

occ_collector([],_,C,C).

occ_collector([H|T],X,C,No):-
    H=X,
    !,
    NewC is C + 1,
    occ_collector(T,X,NewC,No).

occ_collector([H|T],X,C,No):-
    occ_collector(T,X,C,No).


%TAIL RECURSION:
%   - det predicate(1 sol)
%   - the recursive call is the last


%Remove all elements that appear only once
%remove_el(L-list,P-copy,C-collector,R-result)
%remove_el(i,i,i,0)
remove_el([],_,C,C).

remove_el([H|T],P,C,R):-
    occ(P,H,1),
    !,
    remove_el(T,P,C,R).

remove_el([H|T],P,C,R):-
    addToEnd(C,H,Nc), %NC-new collector
    remove_el(T,P,NC,R).


% is_list(H)
% atomic(H) - number
%           - symbol
%           - []
% number(H)