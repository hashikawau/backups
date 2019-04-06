


#==========================================================
#
#==========================================================
CXX=g++
CXXFLAGS= \
         -O0 \
         -g3 \
         -Wall \
         -fmessage-length=0 \
         -MMD \
         -MP \
         --std=c++11 \
         -D__cplusplus=201103L
LINK=g++
LFLAGS=
LIBS= \
     -lboost_system \
     -lboost_filesystem
TARGET=illustlogic.exe

#==========================================================
#
#==========================================================
first:all

#==========================================================
#
#==========================================================
obj/main.o: src/main.cpp
	${CXX} -c ${CXXFLAGS} -o "$@" "$<"

obj/Solver.o: src/Solver.cpp src/Solver.h src/InputDataFile.h src/BinaryMatrix.h src/HintLineSolver.h
	${CXX} -c ${CXXFLAGS} -o "$@" "$<"

obj/InputDataFile.o: src/InputDataFile.cpp src/InputDataFile.h
	${CXX} -c ${CXXFLAGS} -o "$@" "$<"

obj/BinaryMatrix.o: src/BinaryMatrix.cpp src/BinaryMatrix.h
	${CXX} -c ${CXXFLAGS} -o "$@" "$<"

obj/HintLineSolver.o: src/HintLineSolver.cpp src/HintLineSolver.h
	${CXX} -c ${CXXFLAGS} -o "$@" "$<"

obj/HintSolver.o: src/HintSolver.cpp src/HintSolver.h
	${CXX} -c ${CXXFLAGS} -o "$@" "$<"

${TARGET}: obj/main.o obj/Solver.o obj/InputDataFile.o obj/BinaryMatrix.o obj/HintLineSolver.o obj/HintSolver.o
	${LINK} ${LFLAGS} -o ${TARGET} obj/main.o obj/Solver.o obj/InputDataFile.o obj/BinaryMatrix.o obj/HintLineSolver.o obj/HintSolver.o ${LIBS}

#==========================================================
#
#==========================================================
all: ${TARGET}

test-all:
	cd test && make all

#==========================================================
#
#==========================================================
run_1: ${TARGET}
	./${TARGET} test/input/iraroji\(15_15\)-01.txt

clean:
	rm -f ${TARGET} \
	rm -f obj/* \

