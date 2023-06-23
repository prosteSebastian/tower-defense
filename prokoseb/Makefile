#ukradeno a upraveno od: https://gitlab.fit.cvut.cz/husekrad/pa2-cvika-2023/-/blob/master/cv09/semestralka/Makefile
LOGIN = prokoseb
CXX = g++
BASIC_FLAGS = -std=c++17 -O2 -fsanitize=undefined -Wall -pedantic
FLAGS =

LIB_PATHS = -Llibs
LIBS = -lrang -ljson

ZIP = Makefile Doxyfile zadani.txt prohlaseni.txt \
   $(wildcard examples/*) $(wildcard src/*) $(wildcard configFiles/*) $(wildcard testing/*) $(wildcard libs/*) $(wildcard loadGames/*)

SOURCES = $(wildcard src/*.cpp src/*/*.cpp)
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})
DEPS = $(patsubst src/%.cpp, build/%.dep, ${SOURCES})

TEST_SOURCE = $(wildcard testing/*.cpp) $(filter-out src/main.cpp, $(wildcard src/*.cpp src/*/*.cpp))
TEST_OBJECTS = $(patsubst src/%.cpp, build/%.o, ${TEST_SOURCE})
TESTNAME = tester

print: ; @echo ${TEST_SOURCE}

.PHONY: all compile run valgrind doc clean count zip

all: compile doc

compile: ${LOGIN}

${LOGIN}: ${OBJECTS}
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} -Ilibs $^ -o $@

build/%.o: src/%.cpp
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} -Ilib -Ilibs -c $< -o $@

run: compile
	./${LOGIN}

valgrind: compile
	valgrind --leak-check=full ./${LOGIN}

doc: doc/index.html

doc/index.html: Doxyfile $(wildcard src/*)
	doxygen Doxyfile

clean:
	rm -rf build doc
	rm -f ${LOGIN} ${LOGIN}.zip ${TESTNAME}

zip: ${LOGIN}.zip

${LOGIN}.zip: ${ZIP}
	rm -rf tmp/
	rm -f $@
	mkdir -p tmp/${LOGIN}/
	cp --parents -r $^ tmp/${LOGIN}/
	cd tmp/ && zip -r ../$@ ${LOGIN}/
	rm -rf tmp/

build/%.dep: src/%.cpp
	@mkdir -p $(@D)
	${CXX} -MM -MT $(patsubst src/%.cpp, build/%.o, $<) $< > $@

test: ${TESTNAME}

${TESTNAME}: ${TEST_OBJECTS}
	@mkdir -p build/
	${CXX} ${BASIC_FLAGS} ${FLAGS} -Ilibs $^ -o $@

build/testing/%.o: testing/%.cpp
	@mkdir -p build/testing/
	${CXX} ${BASIC_FLAGS} ${FLAGS} -Ilib -Ilibs -c $< -o $@

include ${DEPS}

