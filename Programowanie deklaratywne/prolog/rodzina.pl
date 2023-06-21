kobieta(ewa).
kobieta(elzbieta).
kobieta(iwona).
kobieta(ilona).
kobieta(anna).
kobieta(marta).
kobieta(iza).
kobieta(ola).
kobieta(magda).
kobieta(alicja).
kobieta(zofia).

mezczyzna(piotr).
mezczyzna(adam).
mezczyzna(pawel).
mezczyzna(dariusz).
mezczyzna(jan).
mezczyzna(norbert).
mezczyzna(marek).
mezczyzna(krzysztof).
mezczyzna(maciej).

rodzic(ewa,marek).
rodzic(ewa,marta).
rodzic(piotr,marek).
rodzic(piotr,marta).
rodzic(elzbieta,magda).
rodzic(norbert,magda).
rodzic(maciej,anna).
rodzic(ola,anna).
rodzic(marek,ola).
rodzic(magda,ola).
rodzic(pawel,krzysztof).
rodzic(pawel,iza).
rodzic(iza,alicja).
rodzic(jan,alicja).
rodzic(krzysztof,adam).
rodzic(marta,adam).
rodzic(iwona,iza).
rodzic(iwona,krzysztof).
rodzic(ilona,dariusz).
rodzic(adam,dariusz).
rodzic(ola,zofia).
rodzic(maciej,zofia).

wiek(elzbieta,78).
wiek(norbert,80).
wiek(ewa,84).
wiek(piotr,85).
wiek(iwona,85).
wiek(pawel,86).
wiek(krzysztof,65).
wiek(iza,60).
wiek(marta,55).
wiek(marek,58).
wiek(magda,55).
wiek(maciej,32).
wiek(ola,30).
wiek(adam,37).
wiek(ilona,33).
wiek(dariusz,13).
wiek(anna,10).
wiek(zofia,12).
wiek(jan,61).
wiek(alicja,38).

%zadanie 3   student(X,Y,_,_,_,pp);student(X,Y,_,_,_,uam). lub student(X,Y,_,_,_,K),(K=pp;K=uam).


malzenstwo(M,Z):-rodzic(M,D),rodzic(Z,D),not(M=Z).
ojciec(X,Y):-rodzic(X,Y),mezczyzna(X).
matka(X,Y):-rodzic(X,Y),kobieta(X).
rodzice(M,O,D):-matka(M,D),ojciec(O,D).
dziadek(X,Z):-rodzic(X,Y),rodzic(Y,Z),mezczyzna(X).
babcia(X,Z):-rodzic(X,Y),rodzic(Y,Z),kobieta(X).
dziadkowie(D,B,W):-babcia(B,W),dziadek(D,W),malzenstwo(D,B).
siostra(X,Z):-kobieta(X),rodzic(Y,X),rodzic(Y,Z),not(X=Z).
brat(X,Z):-mezczyzna(X),rodzic(Y,X),rodzic(Y,Z),not(X=Z).
kuzyn(X,Y):-rodzic(Z,X),rodzic(V,Y),rodzic(C,Z),rodzic(C,V).
wuj(X,Y):-brat(X,Z),matka(Z,Y).
stryj(X,Y):-brat(X,Z),ojciec(Z,Y).
ciotka(X,Y):-siostra(X,Z),rodzic(Z,Y).
syn(S,R):-mezczyzna(S),rodzic(R,S).
corka(C,R):-kobieta(C),rodzic(R,C).
przodek(X,Y):-rodzic(X,Y).
przodek(X,Y):-rodzic(X,Z),przodek(Z,Y).


%zadanie 4

starszy(X,Y):-wiek(X,W1),wiek(Y,W2),(W1>W2).
mlodszy(X,Y):-wiek(X,W1),wiek(Y,W2),(W1<W2).

%zadanie 5

nwd(X,0,X).
nwd(X,Y,Z) :- Y > 0, POM is X mod Y, nwd(Y,POM,Z).

%zadanie 6

jest_jaroszem(ola).
jest_jaroszem(ewa).
jest_jaroszem(jan).
jest_jaroszem(pawel).
pije_kawe(iza).
pije_kawe(piotr).
pije_kawe(pawel).
czyta_ksiazki(ola).
czyta_ksiazki(iza).
czyta_ksiazki(pawel).
uprawia_sport(iza).
uprawia_sport(ola).
uprawia_sport(piotr).
uprawia_sport(pawel).

%a)
lubi(ola,X):-jest_jaroszem(X),uprawia_sport(X).
%b)
lubi(ewa,X):-jest_jaroszem(X),\+ pije_kawe(X).
%c)
lubi(iza,X):-uprawia_sport(X),\+ pije_kawe(X).
lubi(iza,X):-czyta_ksiazki(X).
%d)
lubi(janek,X):-uprawia_sport(X).
%e)
lubi(piotr,X):-jest_jaroszem(X),uprawia_sport(X).
lubi(piotr,X):-czyta_ksiazki(X).
%f)
lubi(pawel,X):-jest_jaroszem(X),uprawia_sport(X),czyta_ksiazki(X).

przyjaciele(X,Y):-lubi(X,Y),lubi(Y,X),X\=Y.






