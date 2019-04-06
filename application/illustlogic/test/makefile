
TARGET=test.exe
COMPILE_OPTION=-O0 \
               -g3 \
               -Wall \
               -fmessage-length=0 \
               -MMD \
               -MP \
               --std=c++11 \
               -D__cplusplus=201103L

all:
	g++ ${COMPILE_OPTION} -o${TARGET} main.cpp

clean:
	rm -f ${TARGET}

