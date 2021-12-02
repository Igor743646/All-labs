remove(X, [X|T], T).
remove(X, [Y|T], [Y|T1]) :- remove(X, T, T1).

permute([], []).
permute(L, [X|T]) :- remove(X, L, R), permute(R, T).

predicate(chuk, pn, lozh).
predicate(chuk, vt, lozh).
predicate(chuk, sr, lozh).
predicate(chuk, cht, pravda).
predicate(chuk, pt, pravda).
predicate(chuk, sb, pravda).
predicate(chuk, vs, pravda).

predicate(geck, pn, pravda).
predicate(geck, vt, lozh).
predicate(geck, sr, pravda).
predicate(geck, cht, lozh).
predicate(geck, pt, pravda).
predicate(geck, sb, lozh).
predicate(geck, vs, pravda).

first_is_chuk(chuk, pravda).
first_is_chuk(geck, lozh).
second_is_geck(chuk, lozh).
second_is_geck(geck, pravda).
now_is_pn(_, pravda, pn).
now_is_pn(_, lozh, K) :- K\=pn.
now_is_cht(_, pravda, cht).
now_is_cht(_, lozh, K) :- K\=cht.

answer([FIRST, SECOND], S) :- first_is_chuk(FIRST, X), 
	second_is_geck(SECOND, Y), 
	predicate(FIRST, S, X),
	predicate(SECOND, S, Y),
	now_is_cht(SECOND, Y, S),
	now_is_pn(FIRST, X, S).

task(DATE, FIRST, SECOND) :- permute([chuk, geck], [FIRST,SECOND]), answer([FIRST,SECOND], DATE).