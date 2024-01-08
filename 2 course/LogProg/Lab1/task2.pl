% Task 2: Relational Data

:- ['four.pl'].

student(Group,Surname) :- group(Group,ListGroup), member(Surname,ListGroup).
ball(Surname,C) :- subject(_,ListGrades), member(grade(Surname,C),ListGrades).

% 2.1

sum_list([], 0).
sum_list([Head|Tail], Sum) :-
    sum_list(Tail, TailSum),
    Sum is Head + TailSum.
ball_of_students(Group,C) :- student(Group,Surname), ball(Surname,C).
avarage_ball(Group,Res) :- findall(Res, ball_of_students(Group,Res), List_Result), sum_list(List_Result,Sum), length(List_Result, Length),  Res is Sum/Length.
solve_task1:-write("Группа  | Средний балл\n"),
    findall([Group, Avarage_ball], (group(Group, _), avarage_ball(Group, Avarage_ball)), GroupBall),
    print_group_ball(GroupBall).

print_group_ball([[Group, Avarage_ball] | Rest]) :-
    write("---------------------------\n"),
    write("  "),write(Group), write("   |  "), write(Avarage_ball), write("\n"),
    print_group_ball(Rest).

% 2.2
subject_not_passed(S, Surname) :-
    subject(S, ListGrades),
    member(grade(Surname, 2), ListGrades).

not_passed_subjects :-
    findall([S, Res], (
        subject(S, _),
        findall(Surname, subject_not_passed(S, Surname), Res)
    ), Subjects),
    print_not_passed_subjects(Subjects).

print_not_passed_subjects([[S, Res] | Rest]) :-
    write("---------------------------------------------------\n"),
    write(" "), write(S), write(" |  "), write(Res), write("\n"),
    print_not_passed_subjects(Rest).

solve_task2 :-
    write("         Предмет        |     не сдали студенты\n"),
    not_passed_subjects.

% 2.3

student_not_passed(Group, Surname) :-
    student(Group, Surname),
    ball(Surname, 2).

not_passed_in_groups :-
    findall([Group, Length], (
        group(Group, _),
        findall(Surname, student_not_passed(Group, Surname), Result_List),
        length(Result_List, Length)
    ), GroupsResults),
    print_not_passed_in_groups(GroupsResults).

print_not_passed_in_groups([[Group, Length] | Rest]) :-
    write("------------------------\n"),
    write(" "), write(Group), write("    |   "), write(Length), write("\n"),
    print_not_passed_in_groups(Rest).

solve_task3 :-
    write("Группа  | Не сдалo студентов\n"),
    not_passed_in_groups.