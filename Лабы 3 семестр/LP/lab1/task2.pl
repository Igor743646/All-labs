% Глушатов И.С. Группа: М80-207Б-19

:- ['three.pl'].


pass_exam(X, Y, Z) :- student(_, X, [grade(_, GR1), grade(_, GR2), grade(_, GR3), grade(_, GR4), grade(_, GR5), grade(_, GR6)]),
				GR1>2, GR2>2, GR3>2, GR4>2, GR5>2, GR6>2, Y='Сдал', Z is (GR1+GR2+GR3+GR4+GR5+GR6)/6.
pass_exam(X, Y, Z) :- student(_, X, [grade(_, GR1), grade(_, GR2), grade(_, GR3), grade(_, GR4), grade(_, GR5), grade(_, GR6)]),
				GR1<3, Y='Не сдал', Z is (GR1+GR2+GR3+GR4+GR5+GR6)/6.
pass_exam(X, Y, Z) :- student(_, X, [grade(_, GR1), grade(_, GR2), grade(_, GR3), grade(_, GR4), grade(_, GR5), grade(_, GR6)]),
				GR2<3, Y='Не сдал', Z is (GR1+GR2+GR3+GR4+GR5+GR6)/6.
pass_exam(X, Y, Z) :- student(_, X, [grade(_, GR1), grade(_, GR2), grade(_, GR3), grade(_, GR4), grade(_, GR5), grade(_, GR6)]),
				GR3<3, Y='Не сдал', Z is (GR1+GR2+GR3+GR4+GR5+GR6)/6.
pass_exam(X, Y, Z) :- student(_, X, [grade(_, GR1), grade(_, GR2), grade(_, GR3), grade(_, GR4), grade(_, GR5), grade(_, GR6)]),
				GR4<3, Y='Не сдал', Z is (GR1+GR2+GR3+GR4+GR5+GR6)/6.
pass_exam(X, Y, Z) :- student(_, X, [grade(_, GR1), grade(_, GR2), grade(_, GR3), grade(_, GR4), grade(_, GR5), grade(_, GR6)]),
				GR5<3, Y='Не сдал', Z is (GR1+GR2+GR3+GR4+GR5+GR6)/6.
pass_exam(X, Y, Z) :- student(_, X, [grade(_, GR1), grade(_, GR2), grade(_, GR3), grade(_, GR4), grade(_, GR5), grade(_, GR6)]),
				GR6<3, Y='Не сдал', Z is (GR1+GR2+GR3+GR4+GR5+GR6)/6.


task1(X, L) :- findall([X,Y,Z], pass_exam(X,Y,Z), L).

grades_of_subject('LP', L)  :- findall(G, student(_, _, [grade('LP', G) | _ ]), L).  
grades_of_subject('MTH', L) :- findall(G, student(_, _, [_, grade('MTH', G) | _ ]), L).  
grades_of_subject('FP', L)  :- findall(G, student(_, _, [_, _, grade('FP', G) | _ ]), L).  
grades_of_subject('INF', L) :- findall(G, student(_, _, [_, _, _, grade('INF', G) | _ ]), L).  
grades_of_subject('ENG', L) :- findall(G, student(_, _, [_, _, _, _, grade('ENG', G) | _ ]), L).  
grades_of_subject('PSY', L) :- findall(G, student(_, _, [_, _, _, _, _, grade('PSY', G)]), L).  

count_two([], 0).
count_two([H|T], N) :- H is 2, count_two(T, N1), N is N1 + 1.
count_two([H|T], N) :- H \= 2, count_two(T, N1), N is N1.  

count_notpassed(X, N) :- grades_of_subject(X, L), count_two(L, N).


task2(X, L) :- findall([X, N], count_notpassed(X, N), L).

group_name_midgrade(X, Y, Z) :- student(X, Y, _), pass_exam(Y, _, Z).

group(X, L) :- findall([Y, Z], group_name_midgrade(X, Y, Z), L).

max_grade([[_, GRADE]|[]], GRADE).
max_grade([[_, GRADE]|T], MAX) :- max_grade(T, PASTMAX), MAX is PASTMAX, PASTMAX>GRADE.
max_grade([[_, GRADE]|T], MAX) :- max_grade(T, PASTMAX), MAX is GRADE, PASTMAX<GRADE.
max_grade([[_, GRADE]|T], MAX) :- max_grade(T, PASTMAX), MAX is GRADE, PASTMAX=GRADE.


student_names_with_max_grade(MAXGRADE, [[NAME, GRADE]|[]], [NAME]) :- GRADE is MAXGRADE. 
student_names_with_max_grade(MAXGRADE, [[_, GRADE]|[]], []) :- GRADE \= MAXGRADE. 
student_names_with_max_grade(MAXGRADE, [[NAME, GRADE]|T], [NAME|T1]) :- student_names_with_max_grade(MAXGRADE, T, T1), MAXGRADE is GRADE.
student_names_with_max_grade(MAXGRADE, [[_, GRADE]|T], T1) :- student_names_with_max_grade(MAXGRADE, T, T1), MAXGRADE \= GRADE. 

students_with_max_grade(101, ANS) :- group(101, X), max_grade(X, MAX), student_names_with_max_grade(MAX, X, ANS).
students_with_max_grade(102, ANS) :- group(102, X), max_grade(X, MAX), student_names_with_max_grade(MAX, X, ANS).
students_with_max_grade(103, ANS) :- group(103, X), max_grade(X, MAX), student_names_with_max_grade(MAX, X, ANS).
students_with_max_grade(104, ANS) :- group(104, X), max_grade(X, MAX), student_names_with_max_grade(MAX, X, ANS).

task3(X, L) :- findall([X,Y], students_with_max_grade(X, Y), L).
