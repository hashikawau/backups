
objs = \

include_dirs = \
    ~/work/codes/c++

all:
	make cpp.a

cpp.a: $(objs)
	ar rvs $@ $(objs)

%.o: %.cpp
	g++ -o $@ $< -I $(include_dirs)

#%.o: %.h

