GCC := g++
CFLAGS := -std=c++17 -g
HOMEBREW_PREFIX := /opt/homebrew
HOMEBREW_INCLUDE := $(HOMEBREW_PREFIX)/include
HOMEBREW_LIB := $(HOMEBREW_PREFIX)/lib
clean:
	rm -f *.o *.a *.so
	
	
%.o: %.cpp
	$(GCC) $(CFLAGS) -c $< -o $@ -I$(HOMEBREW_INCLUDE)

all: maze.o
	$(GCC) $(CFLAGS) -o main main.cpp -L$(HOMEBREW_LIB) -I$(HOMEBREW_INCLUDE) -lSDL2 maze.o

run: all 