flags = -pedantic-errors -std=c++11

main.o: main.cpp terminalHelpers.h
	g++ $(flags) -c $<

game: main.o
	g++ $(flags) $^ -o $@

clean:
	rm -rf *.o game save.dat

tar:
	tar -czvf game.tgz *.cpp *.h

.PHONY: clean tar