COMPILER = g++
SRC_FILES = $(wildcard src/*.cpp)
OBJ_FILES := ${subst src,build,$(SRC_FILES)}
OBJ_FILES := ${subst .cpp,.o,$(OBJ_FILES)}

.PHONY: clean run

build/out: $(OBJ_FILES)
	$(COMPILER) $^ -o $@ -lSDL2

build/%.o: src/%.cpp
	$(COMPILER) -c $^ -o $@ -I./include 

clean:
	rm build
	mkdir build

run: build/out
	./$^
