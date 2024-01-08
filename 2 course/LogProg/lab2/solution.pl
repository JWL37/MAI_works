% группа 207Б-22,по списку 19.

std_remove(Elem,[Elem|T],T).
std_remove(Elem,[Y|T],[Y|T1]):-std_remove(Elem,T,T1).
std_permute([],[]).
std_permute(L,[X|T]):-std_remove(X,L,R), std_permute(R,T).

% carpenter-столяр,painter-маляр,plumber-водопроводчик.
solve(Kon,Dav,Fed) :- std_permute([Kon,Dav,Fed],[carpenter,painter,plumber]),not(contradiction([Kon,Dav,Fed])).

contradiction(V):-  data(V,F,A,TF), logicalnot(TF,FT),   data(V,F,A,FT).

logicalnot(true,false).
logicalnot(false,true).

% факты из условия задачи.
data(_,know,[painter,carpenter],true).
data(_,know,[carpenter,painter],true).
data(_,know,[carpenter,plumber],true).
data(_,know,[plumber,carpenter],true).
data(_,know,[painter,plumber],true).
data([_,Dav,Fed],know,[Dav,Fed],false).


print_task():-solve(Kon,Dav,Fed), 
    write("Работа Кондратьева - "), write(Kon), nl,
    write("Работа Давыдова - "), write(Dav), nl, 
    write("Работа Федерова - "), write(Fed),fail.