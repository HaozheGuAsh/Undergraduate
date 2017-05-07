#haozhe gu 999200555
CC=g++
FLAGS= -Wall
 

all:useFraction.cpp calculator.cpp Fraction.h Fraction.cpp
	$(CXX) $(FLAGS) -o calculator calculator.cpp Fraction.h Fraction.cpp
	$(CXX) $(FLAGS) -o useFraction  useFraction.cpp Fraction.h Fraction.cpp       

useFraction:useFraction.cpp Fraction.h Fraction.cpp
	$(CXX) $(FLAGS) -o  $@ $^

calculator:calculator.cpp Fraction.h Fraction.cpp
	$(CC) $(FLAGS) -o $@ $^
clean:
	rm -f calculator useFraction
