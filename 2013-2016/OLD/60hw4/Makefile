family.out : familyRunner.o familytree1.o  
	g++ -ansi -Wall -g -o family.out familyRunner.o familytree1.o  

familyRunner.o : familyRunner.cpp familyRunner.h CPUTimer.h familytree1.h 
	g++ -ansi -Wall -g -c familyRunner.cpp

familytree.o : familytree1.cpp familytree1.h QuadraticProbing.h QuadraticProbing.cpp\
vector.cpp vector.h familyRunner.h QueueAr.h QueueAr.cpp dsexceptions.h mystring.h
	g++ -ansi -Wall -g -c familytree1.cpp 

#QuadraticProbing.o : QuadraticProbing.h QuadraticProbing.cpp
#	g++ -ansi -Wall -g -o QuadraticProbing.o QuadraticProbing.cpp QuadraticProbing.h

clean : 
	rm -f family.out familyRunner.o  familytree.o   

