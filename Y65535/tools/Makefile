# Make is only used for parallelism, not for caching. Use nix-build instead, or
# expect problems.

CXX=g++
CXXFLAGS=																	\
	-std=c++17 																\
	-Wall -Wextra -Wpedantic -Werror -fmax-errors=1 						\
	-ffast-math -O2

LD=g++
LDFLAGS=-lGL -lGLEW -lglfw

CXXSOURCES=$(shell find src -type f -name '*.cpp')
CXXOBJECTS=$(patsubst %.cpp,%.cpp.o,${CXXSOURCES})

a.out: ${CXXOBJECTS}
	${LD} -o $@ $^ ${LDFLAGS}

%.cpp.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<
