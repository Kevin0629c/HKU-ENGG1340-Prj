# Variables
CXX = g++
CXXFLAGS = -w -O2 -std=c++11 -I ../includes/ -Wall 
OBJDIR = .
SRCDIR = ../src
OBJS = $(addprefix $(OBJDIR)/, main.o gameloop.o helpers.o maze2D.o minigame.o pagedmenu.o disjoint.o loader.o)

# Default target
default: game

# Rule to link the game
game: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread

# Rule to compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean target
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o game