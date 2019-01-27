
objs = \
    Arrays.o \
    Calendar.o \
    EventObject.o \
    Random.o

include_dirs = \
    ~/work/codes/c++

all:
	make util.a

util.a: $(objs)
	ar crf $@ $<

%.o: %.cpp
	g++ -c -o $@ $< -I $(include_dirs)

%.o: %.h

