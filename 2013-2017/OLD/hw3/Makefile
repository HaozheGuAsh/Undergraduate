all:battleship
CXXFLAGS=-g -Wall
Ship.o: Ship.cpp Ship.h
Board.o: Board.h Board.cpp
battleship.o:battleship.cpp Ship.h Board.h
battleship: Board.o Ship.o battleship.o
	$(CXX) -o $@ $^ $(LDFLAGS)
clean:
	rm -f *.o battleship

