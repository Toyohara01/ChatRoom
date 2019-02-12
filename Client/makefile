INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall
OBJFILES = Client.o Main.o
LIBS= 

PRODUCT=client

HFILES=Client.hpp
CFILES=Client.cpp main.cpp

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

$(PRODUCT) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(OBJFILES) 

Client.o: Client.cpp Client.hpp
	$(CC) $(CFLAGS) -c Client.cpp

Main.o: main.cpp
	$(CC) $(CFLAGS) -c Main.cpp

clean:
	-rm -f *.o *.d *.exe 
	-rm -f ${PRODUCT} ${GARBAGE}


depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
