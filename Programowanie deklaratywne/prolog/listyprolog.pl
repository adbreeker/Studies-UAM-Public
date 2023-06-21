



%zadanie 4
%a)
suma([],0).
suma([F|R],SUMA):-suma(R,X), SUMA is X+F.

%b)
sumap([],0).
sumap([_],0).
sumap([_,S|R],SUMA):-sumap(R,X), SUMA is X+S.

%c)
suman([],0).
suman([F],F).
suman([F,_|R],SUMA):-suman(R,X), SUMA is X+F.


%zadaie 5 rek
ostatni([X],X).
ostatni([_|Y],OST):-ostatni(Y,OST).

%zadanie 5 not rek
ost(X,O):-reverse(X,Y),Y=[O|_].
% wersja 2
ostb(X,O):-reverse(X,[O|_]).

%zadanie 6
sm([],[],[]).
sm([X|Y],[X1|Y1],[Xs|Ys]):-Xs is X + X1, sm(Y,Y1,Ys).

%zadanie 7 z length
rowne(X,Y):-length(X,A), length(Y,A).

%zadanie 7 bez length
rownenl([],[]).
rownenl([],[_])!.
rownenl([_],[])!.
rownenl([_],[_]).
rownenl([_|R1],[_|R2]):-rownenl(R1,R2).



%zadanie 8
rosnacy([]).
rosnacy([_]).
rosnacy([X,Y|R]):- X=<Y,rosnacy([Y|R]).

%zadanie 9
poczatek([],[]).
poczatek([],X).
poczatek([X],[X]).
poczatek([X|R1],[Y|R2]):-X=Y,poczatek(R1,R2).

%zadanie 10
maxi([],-9999999999).
maxi([X|R],MAX) :-maxi(R,POM),X > POM, MAX is X.
maxi([X|R],MAX) :-maxi(R,POM),X =< POM, MAX is POM.

%zadanie 11

%is_list
tolista([]).
tolista([_|R]) :-tolista(R).

%nextto
obok(X,Y,[])!.
obok(X,Y,[_])!.
obok(X,Y,[X,Y]).
obok(X,Y,[Y,X])!.
obok(X,Y,[X,Y|_]).
obok(X,Y,[_,B|R]):-obok(X,Y,[B|R]).

%numlist
ml(N,N,[N]).
ml(A,Z,[A|R]) :- NextA is A + 1, ml(NextA,Z,R).

%---------------------------------------------------------- listy 2

%zadanie 1

%intersection
przekroj([],_,[]).
przekroj([X|R1], L, [X|R2]) :-member(X, L),przekroj(R1, L, R2).
przekroj([_|R1], L, R2) :-przekroj(R1, L, R2).

%union
suma([],[],[]).
suma(L,[],L).
suma(L, [X|R1], R2):-member(X,L), suma(L,R1,R2).
suma(L, [X|R1], [X|R2]):- \+member(X,L), suma(L,R1,R2).

%subtract
roznica([], _, []).
roznica([X|R], L, L2) :-member(X, L),!,roznica(R, L, L2).
roznica([X|R1], L, [X|R2]) :-roznica(R1, L, R2).

%----------------------------------------------------------- fiboancci
fib(0, 0) :- !.
fib(1, 1) :- !.
fib(N, Result) :- N1 is N - 1, N2 is N - 2, fib(N1, Result1), fib(N2, Result2), Result is Result1 + Result2.

%------------------------------------------------------------ przegl¹danie drzewa
%w g³¹b
preorder(nil,[]).
preorder(tree(E,L,R),N):-preorder(L,L1),preorder(R,R1),append([E|L1],R1,N).

%lewe wierzcholki, korzen, prawe wierzcholki
inorder(nil,[]).
inorder(tree(E,L,R),N):-inorder(L,L1),inorder(R,R1),append(L1,[E|R1],N).

%lewe poddrzewo, prawe poddrzewo, korzeñ
postorder(nil,[]).
postorder(tree(E,L,R),N):-postorder(L,L1),postorder(R,R1),append(L1,R1,N1),append(N1,[E],N).




