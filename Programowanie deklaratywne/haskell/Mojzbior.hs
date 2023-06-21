module Mojzbior (iloczyn_z, suma_z, roznica_z, podzbior_z) where
	
	iloczyn_z [] l2 = []
	iloczyn_z  (l:l1) l2 = if (elem l l2) then l:iloczyn_z l1 l2
				else iloczyn_z l1 l2

	suma_z [] [] = []
	suma_z [] (y:l2) = if (elem y l2) then suma_z [] l2 else y:suma_z [] l2
	suma_z (x:l1) [] = if (elem x l1) then suma_z l1 [] else x:suma_z l1 []

	suma_z (x:l1) (y:l2) 	|  (elem x l1)==True  = suma_z l1 (y:l2)
				|  (elem y l2)==True = suma_z (x:l1) l2
				|  (elem x (y:l2))==True  = suma_z l1 (y:l2)
				|  (elem y (x:l1))==True  = suma_z (x:l1) l2
				|  x<y && (elem x (y:l2))==False = x:suma_z l1 (y:l2)
				|  x>=y && (elem y (x:l1))==False = y:suma_z (x:l1) l2

	roznica_z [] ys = []
	roznica_z (x:xs) ys = if (elem x ys) then roznica_z xs ys
				else x:roznica_z xs ys

	podzbior_z [] [] = True
	podzbior_z _ []  = False
	podzbior_z [] _ = True
	podzbior_z (x:xs) (y:ys) | x == y = podzbior_z xs ys | otherwise = podzbior_z (x:xs) (ys)