


all:
	make lang.a
	make util.a
	make cpp.a

%.a:
	cd $* && make all && cp $@ ..




