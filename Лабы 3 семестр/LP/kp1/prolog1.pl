
parent(nikolai1,maria2).
parent(nikolai1,olga2).
parent(nikolai1,aleksandr2).
parent(aleksandra2,maria2).
parent(aleksandra2,olga2).
parent(aleksandra2,aleksandr2).

parent(pavel1,ekaterina).
parent(pavel1,olga3).
parent(pavel1,anna).
parent(pavel1,nikolai1).
parent(maria_f2,ekaterina).
parent(maria_f2,olga3).
parent(maria_f2,anna).
parent(maria_f2,nikolai1).

parent(aleksandr2,aleksandr3).
parent(aleksandr2,nikolai).
parent(aleksandr2,aleksandra).
parent(maria,aleksandr3).
parent(maria,nikolai).
parent(maria,aleksandra).

parent(aleksandr3,aleksandr).
parent(aleksandr3,xenia).
parent(aleksandr3,nikolai2).
parent(maria_f1,aleksandr).
parent(maria_f1,xenia).
parent(maria_f1,nikolai2).

parent(nikolai2,olga1).
parent(nikolai2,maria1).
parent(nikolai2,alexei).
parent(nikolai2,tatiana).
parent(nikolai2,anasteisha).
parent(aleksandra1,olga1).
parent(aleksandra1,maria1).
parent(aleksandra1,alexei).
parent(aleksandra1,tatiana).
parent(aleksandra1,anasteisha).

ancestor(X,Y):-parent(X,Y).

ancestor(X,Y):-parent(X,Z),ancestor(Z,Y).

