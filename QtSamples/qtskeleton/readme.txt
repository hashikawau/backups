
#eclipse cdt project settings
1. create eclipse cdt project
2. setting eclipse cdt project properties
 - [C/C++ Build] -> [Tool Chain Editor]   : [Current builder] = [Gnu Make Builder]
 - [C/C++ Build]: [Builder Settings] (tab): [Builder type] = [External builder}
                                            uncheck [Use default build command]
                                            [Build command] = [make] (alias of mingw32-make)
                                            uncheck [Generate Makefiles autmatically]
                                            [Build directory] = [${workspace_loc:/${ProjName}/]
 - [C/C++ General] -> [Path and Symbols]: [Includes] (tab): [Include directories] = [C:\lib\Qt\include] (optional to index for cdt editor)
 - [C/C++ General] -> [Processor Include Paths, Macros etc.]: [Entries]  (tab): [CDT User Setting Entries] (tree element): [Name] = __cplusplus , [Value] = 201103L
3. create project's make target (Makefile is created by qmake command)
 - [Target name] = [debug-all] (for debug compile)
 - [Target name] = [release-all] (for release compile)
 - [Target name] = [all] (for debug, release compile)

#qt project settings
1. qmake -project -norecursive src/ (create *.pro file)
2. echo "QT += opengl" 1>>${ProjName}.pro
2. echo "QMAKE_CXXFLAGS += -std=c++11" 1>>${ProjName}.pro
3. qmake (create Makefile)
4. make all (build)


#library path
INCLUDEPATH += .\
                C:/lib/glm
LIBS += -LC:/lib/glew/lib\
        -lopengl32\
        -lglew32

