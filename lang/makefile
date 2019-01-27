
objs = Character.o \
      Exception.o \
      Math.o \
      Number.o \
      Object.o \
      System.o

all:
	make lang.a

lang.a: $(objs)
	ar crf $@ $<

%.o: %.cpp %.h
	g++ -c $< -o $@ -fpermissive

clean:
	rm -f *.o

