CC=gcc
SOURCES=protow.cc
FLAGS=-Wl,--subsystem,windows protow.def
all:
#	gcc -shared -o DLL_file OBJ_files -Wl,--output-def,DEF_file
	${CC} -shared ${SOURCES} ${FLAGS} -o protow.dll 
	${CC} -shared ${SOURCES} ${FLAGS} -o protow.ei.dll -DEASYINJECT