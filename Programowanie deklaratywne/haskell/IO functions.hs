--imports
import Data.Array
-------------------------------------------- cw 7 test

maintest = do
	putStrLn "Hello, what's your name?"
	name <- getLine
	putStrLn ("Hey " ++ name ++ ",you rock!")

------------------------------------------- cw 7 zad 1

io_sir = do
	putStrLn "Give me first number"
	int1 <- getLine
	putStrLn "Give me second number"
	int2 <- getLine
	let a = read int1
	let b = read int2
	let suma = a + b
	let iloczyn = a * b
	let roznica = a - b
	putStrLn "Your results:"
	putStrLn (int1 ++ " + " ++ int2 ++ " = " ++ show suma)
	putStrLn (int1 ++ " * " ++ int2 ++ " = " ++ show iloczyn)
	putStrLn (int1 ++ " - " ++ int2 ++ " = " ++ show roznica)

------------------------------------------ cw 7 zad 2
 
month x | (x == "0" || x == "2" || x == "4" || x == "6" || x == "8") = "0"
	| (x == "1" || x == "3" || x == "5" || x == "7" || x == "9") = "1"
	| otherwise = " blad w peselu!!! "

year x y | (x == "0" || x == "1") = "19" ++ y
	 | (x == "2" || x == "3") = "20" ++ y
	 | (x == "4" || x == "5") = "21" ++ y
	 | (x == "6" || x == "7") = "22" ++ y
	 | (x == "8" || x == "9") = "18" ++ y
	 | otherwise = " blad w peselu!!! "

plec x  | (x == "1" || x == "3" || x == "5" || x == "7" || x == "9") = " urodzony "
	| (x == "0" || x == "2" || x == "4" || x == "6" || x == "8") = " urodzona "
	| otherwise = " blad w peselu!!! "

io_pesel = do
	putStrLn "Imie:"
	name <- getLine
	putStrLn "Nazwisko:"
	surname <- getLine
	putStrLn "Pesel:"
	pesel <- getLine
	let plecB = plec (drop 9 (take 10 pesel))
	let dateB = drop 4 (take 6 pesel) ++ "." ++ month (drop 2 (take 3 pesel)) ++ drop 3 (take 4 pesel) ++ "." ++ year (drop 2 (take 3 pesel)) (take 2 pesel)
	putStrLn (name ++ " " ++ surname ++ plecB ++ show dateB)
	
	 
------------------------------------------- cw 7 zad 3	

nwd a b | a==b =a | a>b =nwd(a-b)(b) | a<b =nwd(a)(b-a)

nww a b =(a*b)/nwd(a)(b)


io_nw = do
	putStrLn "Give me first number"
	int1 <- getLine
	putStrLn "Give me second number"
	int2 <- getLine
	let a = read int1
	let b = read int2
	let nwdshow = nwd a b
	let nwwshow = nww a b
	putStrLn ("NWD(" ++ int1 ++ "," ++ int2 ++ ") = " ++ show nwdshow )
	putStrLn ("NWW(" ++ int1 ++ "," ++ int2 ++ ") = " ++ show nwwshow )

--------------------------------------------- cw 7 zad 4

io_slowa = do
	putStrLn "Give me first word"
	word1 <- getLine
	putStrLn "Give me second word"
	word2 <- getLine
	if length word1 > length word2 then putStrLn ("Krotsze slowo to: " ++ word2)
	else if length word1 < length word2 then putStrLn ("Krotsze slowo to: " ++ word1)
	else putStrLn ("Slowa sa rownej dlugosci")


---------------------------------------------- cw 7 zad 5

-- nie wiedzialem jak zaimportowac ten random wiec trzeba samemu ustalic liczbe :(

random = 47
	

zgadnij = do 
	putStrLn ("Zgadnij liczbe z przedzialu 1-100")
        graj random
 
 

graj secret = do 
	guesses <- proby secret 0
	if (guesses == 404) then putStrLn ("10 nietrafionych, przegrywasz :(")
	else putStrLn ("Wygrales po " ++ show guesses ++ " probach :)")
 
 

proby secret guesses = do 
	if (guesses == 10) then
		do return (404)
	else do
	input <- getLine
        let guess = read input :: Int
        if (guess == secret) then
        	do return (guesses + 1)
      	else if guess < secret then do 
		putStrLn ("Za mala!")
        	proby secret (guesses + 1)
        else do 
		putStrLn ("Za duza!")
        	proby secret (guesses + 1)        


---------------------------------------------------------- cw 8 zad 1

usun_dupl a [] = []
usun_dupl a (x:xs)	| a == x = [] ++ usun_dupl a xs
			| otherwise = [x] ++ usun_dupl a xs

licz_wyst a [] = 1
licz_wyst a (x:xs)	| a == x =1 + licz_wyst a xs
			| otherwise =0 + licz_wyst a xs



przypisz_wyst [] = []
przypisz_wyst (x:xs) = [(x , licz_wyst x xs)] ++ przypisz_wyst (usun_dupl x xs)
	
	 

---------------------------------------------------------- cw 8 zad 2

diff [] [] = ""
diff (x:xs) [] = "-" ++ diff xs []  
diff [] _ = ""
diff (x:xs) (y:ys) = if x==y then [x] ++ diff (xs) (ys)
		else "-" ++ diff (xs) (ys)
                      

-------------------------------------------------------- cw 8 zad 3


-------------------------------------------------------- cw 8 zad 4


---------------------------------------------------------cw 8 zad 5

--------------------------------------------------------- cw 8 zad 6

skladowe :: Int -> Int -> [[Int]]
skladowe wielkosc ilosc = tab ! (wielkosc, ilosc, wielkosc)
	where
    		tab   = listArray ((1, 1, 1), (wielkosc, ilosc, wielkosc)) wypelnienie
    		wypelnienie       = [f i j k | i <- [1 .. wielkosc], j <- [1 .. ilosc], k <- [1 .. wielkosc]]

    		f i 1 k = if i > k `min` wielkosc then [] else [[i]]
    		f i j k = [(d:ds) | d <- [1 .. k `min` pred i], ds <- tab ! (i - d, j - 1, d)]


pomocnicza n i 	| i<=n =skladowe n i ++ pomocnicza n (i+1)
		| otherwise =[]


sumujace n = pomocnicza n 1

	
