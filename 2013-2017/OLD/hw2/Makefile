all: testShip

CXXFLAGS=-g -Wall

Ship.o: Ship.cpp Ship.h
testShip.o: testShip.cpp Ship.h

testShip: testShip.o Ship.o
	$(CXX) -o $@ $^  $(LDFLAGS)

clean:
	rm -f *.o testShip
