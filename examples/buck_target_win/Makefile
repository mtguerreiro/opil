
DIR_GUARD := if not exist build mkdir build
OPIL      := ../..
SOCK_LIB  := ws2_32
OBJS      := build/ctlrif.o build/targetCommWinSock.o build/opiltarget.o build/buckcontrol.o

main: ${OBJS} src/main.c
	gcc -c src/main.c -I${OPIL}/ -o build/main.o
	gcc build/main.o ${OBJS} -l${SOCK_LIB} -o build/opiltarget.exe

build/ctlrif.o: ${OPIL}/ctlrif/ctlrif.c
	${DIR_GUARD}
	gcc -c ${OPIL}/ctlrif/ctlrif.c -I${OPIL}/ -o build/ctlrif.o
	
build/targetCommWinSock.o: ${OPIL}/comm/win/targetCommWinSock.c
	${DIR_GUARD}
	gcc -c ${OPIL}/comm/win/targetCommWinSock.c -I${OPIL}/ -o build/targetCommWinSock.o

build/opiltarget.o: ${OPIL}/opiltarget.c
	${DIR_GUARD}
	gcc -c ${OPIL}/opiltarget.c -I${OPIL}/ -o build/opiltarget.o

build/buckcontrol.o: src/buckcontrol.c
	${DIR_GUARD}
	gcc -c src/buckcontrol.c -I${OPIL}/ -o build/buckcontrol.o

clean:
	del /q build
	
