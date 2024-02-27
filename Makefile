flags = -pedantic-errors -std=c++11

%.o: %.cpp %.hpp
	g++ $(flags) -c $< -o $@

game: main.o maze2D.o helpers.o disjoint.o
	g++ $(flags) $^ -o $@

clean:
	rm -rf *.o game

tar:
	tar -czvf game.tgz *.cpp *.hpp

.PHONY: clean tar