
objs = \
    Test.o \
    TestComponent.o \
    TestContainer.o \
    TestJoystick.o \
    TestLabel.o \
    TestMath.o \
    TestString.o \
    TestStringBuffer.o

include_dirs = \
    ~/work/codes/c++

all:
	make windows.a

%.a: $(objs)
	ar crf $@ $< -I $(include_dirs)

%.o: %.cpp
	g++ -o $* $<

%.o: %.h

illustlogic.exe:
	#/c/dm/bin/dmc.exe -oillustlogic.exe -Aer -WD gdi32.lib comdlg32.lib winmm.lib IllustrationLogic.cpp
	/c/dm/bin/dmc.exe -oillustlogic.exe -Aer -L/SU:windows gdi32.lib comdlg32.lib winmm.lib IllustrationLogic.cpp

clean:
	rm illustlogic.exe


