% группа 207Б-22,по списку 19.

std_len([],0).
std_len([_|Tail],Size) :- std_len(Tail,Size1), Size is Size1+1.

std_member(Element, [Element|_]).
std_member(Element, [_|Tail]) :- std_member(Element, Tail).

std_append([], List, List).
std_append([Head|BeginTail], AddList, [Head|Result]) :- std_append(BeginTail,AddList,Result).

std_remove(Elem,[Elem|T],T).
std_remove(Elem,[Y|T],[Y|T1]):-std_remove(Elem,T,T1).

std_permute([],[]).
std_permute(L,[X|T]):-std_remove(Elem,L,R),std_permute(R,T).

std_sublist([],[]).
std_sublist(S,L):-
    std_append(_, L1,L), std_append(S,_,L1).

% 1.1
get_last_element([Elem], Elem).
get_last_element([_|Tail], Elem) :- get_last_element(Tail, Elem).

get_last_element_with_std(List, Last) :-append(_, [Last], List).    

% 1.2

scalar_mult_without_std([], [], 0).

scalar_mult_without_std([], [Elem_second_vector | Rest_part_vector_2], Result) :-
    scalar_mult_without_std([0], [Elem_second_vector | Rest_part_vector_2], Result).

scalar_mult_without_std([Elem_first_vector | Rest_part_vector_1], [], Result) :-
    scalar_mult_without_std([Elem_first_vector | Rest_part_vector_1], [0], Result).

scalar_mult_without_std([Elem_first_vector | Rest_part_vector_1], [Elem_second_vector | Rest_part_vector_2], Result) :-
    scalar_mult_without_std(Rest_part_vector_1, Rest_part_vector_2, SubResult), 
    Result is Elem_first_vector * Elem_second_vector + SubResult.



add_zero_vector(List, N, Finished) :-
    length(List, Len),
    (Len =:= N -> Finished = List; 
        Len < N -> 
            append(List, [0], NewList),
            add_zero_vector(NewList, N, Finished);
        Finished = List).

scalar_mult(V1, V2, Result) :-
    length(V1, Len1),
    length(V2, Len2),
    MaxLen is max(Len1, Len2),
    add_zero_vector(V1, MaxLen, NewV1),
    add_zero_vector(V2, MaxLen, NewV2),
    scalar_mult_calculation(NewV1, NewV2, Result).


scalar_mult_calculation([], [], 0).
scalar_mult_calculation([Elem_first_vector|Rest_part_vector_1], [Elem_second_vector|Rest_part_vector_2], Result) :-
    scalar_mult_calculation(Rest_part_vector_1, Rest_part_vector_2, SubResult),
    Result is SubResult + Elem_first_vector * Elem_second_vector.
