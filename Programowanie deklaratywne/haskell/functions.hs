sgn x 	| x<0 =(-1)
	| x==0 =0
	| x>0 =1

-------------------------------------------------
		
sil x	| x==1 =1
	| x>1 =x*sil(x-1)


-------------------------------------------------cw 1 zad 1

function x | x>2 =x^2 | 2>=x && x>0 =x-1 | x<=0 =abs(x)

--------------------------------------------------cw 1 zad 2

vst r h =3.14*r^2*h*(1/3)

-------------------------------------------------cw 1 zad 3

pw r h =3.14*2*r*h

-------------------------------------------------cw 1 zad 4

pow1 a n | n==0 =1 | n>0 =a*pow1(a)(n-1)

------------------------------------------------cw 1 zad 5

comp a b | ((a+b) `mod` 2)==0 ="parzysta" | otherwise ="nieparzysta"

------------------------------------------------cw 1 zad 6

ciag1 i | i==1 =5 | i>1 =2*ciag1(i-1)-1

-------------------------------------------------cw 1 zad 7

fib1 i | i==1 =1 | i==2 =1 | i>2 =fib(i-1)+fib(i-2)

--------------------------------------------------cw 1 zad 8

isfib x i | x==fib1(i) ="tak" | otherwise ="nie"

---------------------------------------------------cw 1 zad 9

nwd a b | a==b =a | a>b =nwd(a-b)(b) | a<b =nwd(a)(b-a)

----------------------------------------------------cw 1 zad 10

nww a b =(a*b)/nwd(a)(b)

----------------------------------------------------cw 1 zad 11

istriangle a b c 	| (c>=a && c>=b && (a+b)>c) ="tak"
			| (b>=a && b>=c && (a+c)>b) ="tak"
			| (a>=c && a>=b && (c+b)>a) ="tak" 
			| otherwise ="nie"

------------------------------------------------

fib n = fibPOM n 1 1
fibPOM n f1 f2 = if n==1 then f1 
		else fibPOM(n-1) (f1+f2) f1

------------------------------------------------- cw 2 zad 1

pow a x = powPOM a x 1 
powPOM a x f1 = if x==0 then f1
		else powPOM a (x-1) (f1*a) 

-------------------------------------------------

powREC a n | n==0 =1 | n>0 =a*pow(a)(n-1)

-------------------------------------------------

nofa n = nofaPOM n 3 1
nofaPOM n f1 f2 = if n == 1 then f1
		else if n == 2 then f2
			else nofaPOM (n-1) (f2) (2*f2-f1)


-------------------------------------------------- cw 2 zad 2

root ::  Float->Float->Float->Float



root a b c = if a==0 then 404
		else if b^2-4*a*c<0 then 404
			else if b^2-4*a*c == 0 then -b/2*a
				else (-b + sqrt(b^2-4*a*c)) / 2*a

----------------------------------------------------------

f 0 = []
f n = n:f(n-1)

----------------------------------------------------cw 4 zad 1
 
ciagNOTREC a b q = [a+x*q | x <- [0..b], a+x*q <= b]


ciagREC a b q | a>b =[]
ciagREC a b q  = a:ciagREC(a+q)(b)(q)

---------------------------------------------------- cw 4 zad 2

wycinekNOTREC a b xs = [xs!!(i-1) | i <- [a..b]]

wycinekREC a b xs | a==b =[xs!!(b-1)]
wycinekREC a b xs = xs!!(a-1):wycinekREC(a+1)(b)(xs)

---------------------------------------------------- cw 4 zad 3

numerowanie i [] = []
numerowanie i (x:xs) = (i,x):numerowanie(i+1)(xs)

---------------------------------------------------- cw 4 zad 4

iloczyn_z [] l2 = []
iloczyn_z  (l:l1) l2 = if (elem l l2) then l:iloczyn_z l1 l2
			else iloczyn_z l1 l2

----------------------------------------------------- cw 4 zad 5
suma_z [] [] = []
suma_z [] (y:l2) = if (elem y l2) then suma_z [] l2 else y:suma_z [] l2
suma_z (x:l1) [] = if (elem x l1) then suma_z l1 [] else x:suma_z l1 []

suma_z (x:l1) (y:l2) 	|  (elem x l1)==True  = suma_z l1 (y:l2)
			|  (elem y l2)==True = suma_z (x:l1) l2
			|  (elem x (y:l2))==True  = suma_z l1 (y:l2)
			|  (elem y (x:l1))==True  = suma_z (x:l1) l2
			|  x<y && (elem x (y:l2))==False = x:suma_z l1 (y:l2)
			|  x>=y && (elem y (x:l1))==False = y:suma_z (x:l1) l2


suma_zEASY l1 l2 = l1++l2

sumaZroznicy l1 l2 = l1 ++ roznica_z l2 l1

			
------------------------------------------------------ cw 4 zad 6

roznica_z [] ys = []
roznica_z (x:xs) ys = if (elem x ys) then roznica_z xs ys
			else x:roznica_z xs ys

------------------------------------------------------- cw 4 zad 7

powerlist [] = [[]]
powerlist (x:xs) = powerlist xs ++ [x:li | li <- powerlist xs]

------------------------------------------------------- cw 4 zad 9

nalezy x xs = foldl (\nal y -> if y==x then True else nal) False xs


---------------------------------------------------------- cw 5 zad 1
--jedna zmiennna
--(\x -> x**x) 3
--(\x -> (x+x)*x) 4

--dwie zmienne
--(\x -> (\y -> x*y)) 3 4
--(\x -> (\y -> x**y**x)) 2 3

--trzy zmienne
--(\x -> (\y -> (\z -> (x+y)**z))) 2 3 4
--(\x -> (\y -> (\z -> (x/y)/z))) 2 3 4

---------------------------------------------------------- cw 5 zad 2

data MOTO = Audi | Alfa_Romeo | BMW | Polonez | Lamborgini
		deriving (Show)

autoFROM :: Kraj -> MOTO
type Kraj = [Char]

autoFROM kraj 	| kraj == "Wlochy" = Lamborgini
		| kraj == "Niemcy" = BMW
		| kraj == "Polska" = Polonez
		| kraj == "Francja" = Alfa_Romeo
		| kraj == "Belgia" = Audi

autoSPEED :: MOTO -> String
autoSPEED auto = case auto of
		Audi -> "190km/h"
		Alfa_Romeo -> "210km/h"
		Polonez -> "130km/h"
		BMW -> "200km/h"
		Lamborgini -> "299km/h"

----------------------------------------------------------- cw 5 zad 3

data Uczelnia = UAM | UJ | UEP | PG | PP
		deriving (Show)

uczelniaINFO :: Uczelnia -> (Int, String)
uczelniaINFO uczelnia = case uczelnia of 
			UAM -> (1998 , "Poznan")
			UJ -> (1634 , "Krakow")
			UEP -> (2010 , "Elblag")
			PG -> (1873 , "Gdansk")
			PP -> (2001 , "Poznan")

--------------------------------------------------------- cw 5 zad 4
	
data Tree a = Empty | Node a (Tree a) (Tree a)
		deriving (Show)


treeA :: Tree Int
treeA = Node 1 
	(Node 2
		(Node 4 
			Empty
			Empty)
		(Node 5 
			Empty 
			(Node 8 
				Empty 
				Empty)))
	(Node 3 
		(Node 6 
			Empty 
			(Node 9 
				Empty 
				Empty))
		(Node 7 
			Empty 
			Empty))



treeF :: Tree Int
treeF = Node 1 
	(Node 2
		(Node 4 
			Empty
			(Node 8 
				Empty 
				Empty))
		(Node 5 
			Empty 
			(Node 8 
				Empty 
				Empty)))
	(Node 3 
		(Node 6 
			Empty 
			(Node 9 
				Empty 
				Empty))
		(Node 7 
			(Node 8 
				Empty 
				Empty)
			Empty))


treeB :: Tree Char
treeB = Node 'a'
		(Node 'b'
			Empty
			(Node 'd'
				(Node 'f'
					Empty
					Empty)
				Empty))

		(Node 'c'
			(Node 'e'
				Empty
				(Node 'g'
					Empty
					Empty))
			Empty)

----------------------------------------------------------- drzewa testowe

treeC :: Tree Int
treeC = Node 5 
		Empty
		(Node 8 Empty Empty)

treeD :: Tree Int
treeD = Node 5 
		(Node 7 Empty Empty)
		(Node 8 Empty Empty)

treeE :: Tree Int
treeE = Node 8 
		Empty
		(Node 5 Empty Empty)

------------------------------------------------------------ funkcje do drzew

depth :: Tree a -> Int
depth Empty = 0 
depth (Node _ l r) = 1 + max (depth l) (depth r)

preorder :: Tree a -> [a] 
preorder Empty = [] 
preorder (Node a l r) = [a] ++ preorder l ++ preorder r

inorder :: Tree a -> [a] 
inorder Empty = [] 
inorder (Node a l r) = inorder l ++ [a] ++ inorder r

postorder :: Tree a -> [a] 
postorder Empty = [] 
postorder (Node a l r) = postorder l ++ postorder r ++ [a]

------------------------------------------------------------ cw 5 zad 5

toList :: Tree a -> [a] 
toList Empty = [] 
toList (Node a l r) = [a] ++ toList l ++ toList r

treeMemberE x a = if (elem x (toList a)) then True
		else False

treeMemberNE x Empty = False
treeMemberNE x (Node a l r) = if x == a then True
				else if treeMemberNE x l == False && treeMemberNE x r == False then False
					else True




------------------------------------------------------------ cw 5 zad 6


--toList :: Tree a -> [a] 
--toList Empty = [] 
--toList (Node a l r) = [a] ++ toList l ++ toList r

subtree x Empty = False
subtree x (Node a l r) = if toList x == toList l || toList x == toList r then True
			else if subtree x l == False && subtree x r == False then False
				else True


------------------------------------------------------------ cw 5 zad 7

polacz xs [] = xs
polacz [] xs = xs
polacz (x:xs) (y:ys) = (++) x y : polacz xs ys

wszerz Empty = []
wszerz (Node a l r) = [[a]] ++ polacz (wszerz l) (wszerz r)


------------------------------------------------------------ cw 6 zad 1			 

-- w pliku Mojzbior.hs i testMojzbior.hs
	
	

------------------------------------------------------------ cw 6 zad 2

errorvalue = 404
mindepth :: Tree a -> Int 
mindepth Empty = 1
mindepth (Node _ Empty Empty) = errorvalue
mindepth (Node _ l r) = if mindepth l == errorvalue || mindepth r == errorvalue then 0 + min (mindepth l) (mindepth r)
				else 1 + max (mindepth l) (mindepth r)	



------------------------------------------------------------- cw 6 zad 3

data TreeTet a = Emptyy | Nodee a (TreeTet a) (TreeTet a) (TreeTet a)
		deriving (Show)

treeTetA :: TreeTet Int
treeTetA = Nodee 1
		(Nodee 2
			(Nodee 3 Emptyy Emptyy Emptyy)
			Emptyy
			Emptyy)
		(Nodee 4 Emptyy Emptyy Emptyy)
		(Nodee 5 Emptyy Emptyy Emptyy)


sumtree :: TreeTet Int -> Int
sumtree Emptyy = 0
sumtree (Nodee a l r t) = a + sumtree l + sumtree r + sumtree t

------------------------------------------------------------ cw 6 zad 4

class Cherek imie
data Adam = Energiczny | Zaspany
		deriving(Show)
instance Cherek Adam 
	
happy :: Adam -> Bool
happy Energiczny = True
happy Zaspany = False

-- funkcja przypisuje wartoœæ prawdy lub fa³szu w zale¿noœci od tego czy Adam 
-- jest energiczny czy zmêczony, przepraszam ale nie rozumiem za bardzo tego tematu i 
-- tym samym nie potrafi³em wymysliæ czegoœ bardziej skomplikowanego




















