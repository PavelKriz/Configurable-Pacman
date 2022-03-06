CXX=g++ #compiler
#source files
src = $(wildcard src/*.cpp) \
	$(wildcard src/game/*.cpp) \
	$(wildcard src/view/*.cpp)
#object files
obj = $(src:.cpp=.o)

CXXFLAGS = -Wall -pedantic -O2 -Werror #compile flags

LFLAGS = -lSDL2 -lSDL2_image #link flags

#get all generated things from code
all: pacman

#compile all code
compile: pacman

# compiling rule
%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# linking all the files
pacman: $(obj)
	$(CXX) -o $@ $^ $(LFLAGS)


#run made binary
.PHONY: run
run: pacman
	cp -r examples/images images
	./pacman ./examples/testConfig ./examples/testMap
	rm -r images

#clean all object files and binary
.PHONY: clean
clean:
	rm -f $(obj) pacman
