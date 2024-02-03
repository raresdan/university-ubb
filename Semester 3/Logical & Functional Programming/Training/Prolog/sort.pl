% a. Sort a list with removing the double values. E.g.: [4 2 6 2 3 4] --> [2 3 4 6]
% b. For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to sort every 
% sublist with removing the doubles.
% Eg.: [1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
% [1, 2, [1, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1], 7].


remove_duplicates([],[]).
remove_duplicates([H1,H2|T], Result):-
    H1 =:= H2,
    remove_duplicates(T, TempResult),
    Result = [H1|TempResult].
remove_duplicates([H|T], Result):-
    remove_duplicates(T,TempResult),
    Result = [H|TempResult].

sorted_unique([],[]).
sorted_unique(List, Result):-
    sort(List, Sorted),
    remove_duplicates(Sorted, Unique),
    sort(Unique, Result).

heterogeneous_processing([],[]).
heterogeneous_processing([H|T], Result):-
    is_list(H),
    sorted_unique(H, SortedH),
    heterogeneous_processing(T, TempResult),
    Result = [SortedH|TempResult].
heterogeneous_processing([H|T], Result):-
    heterogeneous_processing(T, TempResult),
    Result = [H|TempResult].