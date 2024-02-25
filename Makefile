flags = -pedantic-errors -std=c++11

main.o: main.cpp terminalHelpers.hpp termcolor.hpp
	g++ $(flags) -c $<

game: main.o
	g++ $(flags) $^ -o $@

clean:
	rm -rf *.o game

tar:
	tar -czvf game.tgz *.cpp *.hpp

.PHONY: clean tar