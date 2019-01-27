

all:
	make app01
	make commandLine01
	make commandLine02
	make main03
	make makefile
	make sdk03
	make sdk05
	make sdk06
	make sdk07
	make sdk08
	make sdk09
	make skeleton
	make window01
	make window02
	make window03

%: %.cpp
	g++ $< -o $@ -fpermissive -mwindows -lgdi32

clean:
	rm -f *.exe


