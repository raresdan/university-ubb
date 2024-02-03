% 4.
% The list a1... an is given. 
% Write a predicate to determine all sublists strictly ascending of this list a


% Helper functions

% Checks if a list is strictly ascending
strictly_ascending([]).
strictly_ascending([_]).
strictly_ascending([X, Y | Rest]) :-
    X < Y,
    strictly_ascending([Y | Rest]).

% Generates subsets with strictly ascending numbers
generate_subsets([], []).
generate_subsets([X | Rest], [X | Subset]) :-
    generate_subsets(Rest, Subset),
    strictly_ascending([X | Subset]).
generate_subsets([_ | Rest], Subset) :-
    generate_subsets(Rest, Subset).


print_list([]) :- nl.
print_list([H | T]) :-
    write(H),
    write(' '),
    print_list(T).


% Main function

main(List, Subset) :-
    generate_subsets(List, Subset),
    print_list(Subset),
    fail.
main(_).





