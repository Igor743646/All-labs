% Глушатов И.С. Группа: М80-207Б-19

% Стандартные предикаты
size([], 0).
size([_|Y], N) :- size(Y, N1), N is N1 + 1. 

member(A, [A|_]).
member(A, [_|Z]) :- member(A, Z).

append([], X, X).
append([A|X], Y, [A|Z]) :- append(X, Y, Z).

remove(X, [X|T], T).
remove(X, [Y|T], [Y|T1]) :- remove(X, T, T1).

permute([], []).
permute(L, [X|T]) :- remove(X, L, R), permute(R, T).

% Усечение списка до указанной длины в двух вариантах (7 вариант)
cutlst(_, [], []).
cutlst(NUMI, [_|_], []) :- NUMI==0.
cutlst(NUMI, [H|T], [H|T1]) :- NUMO is NUMI-1, cutlst(NUMO, T, T1), NUMI>0.

cutlst_with_std(_, [], []).
cutlst_with_std(NUMI, [_|_], []) :- NUMI=0.
cutlst_with_std(NUMI, [H|T], T1) :- NUMO is NUMI-1, cutlst_with_std(NUMO, T, T2), append([H], T2, T1), NUMI>0.

% Нахождение позиции минимального элемента в списке в двух вариантах (12 вариант)
position(A, [A|_], I) :- I is 0. 
position(A, [_|T], I) :- position(A, T, I1), I is I1+1.

min([H|[]], H).
min([H|T], ELEM) :- min(T, ELEM1), H>ELEM1, ELEM is ELEM1.
min([H|T], ELEM) :- min(T, ELEM1), H<ELEM1, ELEM is H.
min([H|T], ELEM) :- min(T, ELEM1), H==ELEM1, ELEM is H.

position_of_min([H|T], I) :- min([H|T], MP), position(MP, [H|T], I).


first_elem_of_list([H|_], H).
id_elem_of_list(ID, [H|_], H) :- ID is 0.
id_elem_of_list(ID, [_|T], R) :- ID \= 0, NEWID is ID-1, id_elem_of_list(NEWID, T, R).

position_of_min_with_std(LIST, 0) :- size(LIST, 1).
position_of_min_with_std(LIST, I) :- first_elem_of_list(LIST, FIRST), remove(FIRST, LIST, T), position_of_min_with_std(T, LASTI), id_elem_of_list(LASTI, T, R), R<FIRST, position(R, LIST, I).
position_of_min_with_std(LIST, I) :- first_elem_of_list(LIST, FIRST), remove(FIRST, LIST, T), position_of_min_with_std(T, LASTI), id_elem_of_list(LASTI, T, R), R>FIRST, I is 0.
position_of_min_with_std(LIST, I) :- first_elem_of_list(LIST, FIRST), remove(FIRST, LIST, T), position_of_min_with_std(T, LASTI), id_elem_of_list(LASTI, T, R), R==FIRST, I is 0.
