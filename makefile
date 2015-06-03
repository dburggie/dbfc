
INSTALLDIR = ~/bin
BLD = build

INC = -Isource
CFLAGS = -Wall
CC = gcc ${CFLAGS} ${INC}

OBJ = build/main.o build/compile.o
EXE = dbfc
INX = ${INSTALLDIR}/${EXE}


all: ${BLD} ${OBJ} ${EXE}

clean:
	rm -f ${OBJ}
	rm -f ${EXE}
	rm -f output.bf.c
	rm -f a.out

install: ${INX}

uninstall:
	rm -f ${INX}

${BLD}:
	mkdir -p ${BLD}

${INSTALLDIR}:
	mkdir -p ${INSTALLDIR}

${INX}: ${INSTALLDIR} ${EXE}
	cp ${EXE} $@

${EXE}: ${OBJ}
	${CC} -o $@ $^

${BLD}/main.o: source/main.c source/compile.h
	${CC} -o $@ -c $<

${BLD}/compile.o: source/compile.c source/compile.h
	${CC} -o $@ -c $<


