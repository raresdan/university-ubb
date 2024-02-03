% 4.
% a. Write a predicate to determine the sum of two numbers written in list representation.
% b. For a heterogeneous list, formed from integer numbers and list of digits, write a predicate to compute the 
% sum of all numbers represented as sublists.
% Eg.: [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] => [8, 2, 2].


%Helper functions

% Transforms a given list containing the digits into a number
% list_to_number(+List, -Result).
%               (i,o)
list_to_number([], 0).
list_to_number([Digit|Rest], Number) :-
    list_to_number(Rest, RestNumber),
    length(Rest, NumDigits),
    Power is 10 ** NumDigits,
    Number is Digit * Power + RestNumber.


% Transforms a number into a list containing its digits
% number_to_list(+Number, -Result).
%               (i,o)
number_to_list(0, []).
number_to_list(Number, Digits) :-
    Number > 0,
    Digit is Number mod 10,
    NewNumber is Number // 10,
    number_to_list(NewNumber, RestDigits),
    Digits = [Digit|RestDigits].


% Gets all the sublists of digits and transforms them into numbers
% get_numbers(+List, -Result).
%                 (i, o)
get_numbers([], []).
get_numbers([H|T], Result):-
    (is_list(H) -> % If H is a list convert it to a number
        list_to_number(H, Number),
        get_numbers(T, RestNumbers),
        Result = [Number|RestNumbers]
    ;
        get_numbers(T, Result)
    ).


% Computes the sum of all elements in a list
% compute_sum(+List, -Result)
compute_sum([], 0).
compute_sum([X|Xs], Sum) :-
    compute_sum(Xs, RestSum),
    Sum is X + RestSum.



%Main functions

%sum_two_sublists(+List, +List, -Result).
sum_two_sublists([], [], []).
sum_two_sublists(List1, List2, Result):-
    list_to_number(List1, Number1),
    list_to_number(List2, Number2),
    Result is Number1 + Number2.


%sum_all_sublists(+List, -Result).
sum_all_sublists([], []).
sum_all_sublists(List, Result):-
    get_numbers(List, Numbers),
    compute_sum(Numbers, Sum),
    number_to_list(Sum, Result).
