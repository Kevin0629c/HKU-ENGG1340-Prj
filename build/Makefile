# Variables
CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wno-missing-braces -I ../includes/
OBJDIR = .
SRCDIR = ../src
OBJS = $(addprefix $(OBJDIR)/, main.o gameloop.o helpers.o maze2D.o minigame.o pagedmenu.o disjoint.o)

# Default target
default: game

# Rule to link the game
game: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean target
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o game