flags = -pedantic-errors -std=c++11

main.o: main.cpp terminalHelpers.hpp termcolor.hpp gameflow.hpp
	g++ $(flags) -c $<

gameflow.o: gameflow.cpp gameflow.hpp terminalHelpers.hpp termcolor.hpp
	g++ $(flags) -c $<

game: main.o gameflow.o
	g++ $(flags) $^ -o $@

clean:
	rm -rf *.o game

tar:
	tar -czvf game.tgz *.cpp *.hpp

.PHONY: clean tar