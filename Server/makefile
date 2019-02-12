INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall
OBJFILES = Server.o Main.o
LIBS= 

PRODUCT=main

HFILES= Server.hpp
CFILES= Server.cpp main.cpp

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

$(PRODUCT) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(OBJFILES) 

Server.o: Server.cpp Server.hpp
	$(CC) $(CFLAGS) -c Server.cpp

Main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp


clean:
	-rm -f *.o *.d *.exe 
	-rm -f ${PRODUCT} ${GARBAGE}


depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
