
objects = \
          MenuFile.o \
          IllustrationLogic.o \

all:
	make illustlogic

illustlogic: $(objects)
	g++ -o $@ $(objects) -lgdi32

%.o: %.cpp %.h
	g++ -o $@ $*.cpp -I ../

#illustlogic.exe:
#	/c/dm/bin/dmc.exe -oillustlogic.exe -Aer -L/SU:windows gdi32.lib comdlg32.lib winmm.lib IllustrationLogic.cpp

clean:
	rm illustlogic.exe


	#/c/dm/bin/dmc.exe -oillustlogic.exe -Aer -WD gdi32.lib comdlg32.lib winmm.lib IllustrationLogic.cpp
