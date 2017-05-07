ECS127 Homework2 Haozhe Gu 999200555

the cpp file decipher.cpp is my program to crack the cipher text.

I create the function getpermutaion to get true random permutation, that is,
when i run the program for the second time, the permutation will be totally different from when i first run the program.

Thus, the iteration step requires might  be different because of differnt start point and paths.

Sometime, it might stuck in some permutation. Then I let it restart the iteration steps with new start point.

The cracked cipher text (M) is :

when i heard the learned astronomer   when the proofs  the figures  were ranged in columns before me   when i was shown the charts and diagrams  to add  divide  and measure them   when i sitting heard the astronomer where he lectured with much applause in the  lecture room   how soon unaccountable i became tired and sick   till rising and gliding out i wandered off by myself   in the mystical moist night air  and from time to time   looked up in perfect silence at the stars

The key f is i h c w n a m k l g d o j e r u f x y t b v q p z s

The ln(Pl(f)) plausibility of f is -2551.46

Normally, before 2000 iteration steps, the permutation will only have 2 or 4  out of 26 mismatched map.

Then, if not stucked, it can get the right permutation within 400 iteration steps. That is, it can decipher the cipher text after about 2400 iterations.


##############
One thing about the file decipher.cpp: You need to use -std=c++11 to compile the file because the library to apply natural log or expotential required 
C++ 11.  
	
Probably use the cipher.txt provided as cipher text. because i used specific ln(Pl(f)) to make sure the final permutation is not the stucked one.
runed on pc33. 
