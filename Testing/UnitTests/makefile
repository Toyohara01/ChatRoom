INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
PFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall -g
CFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall -g --coverage
SOCKETTESTSOBJFILES = Server.o Client.o SocketTests.o
LIBS= 

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

SOCKETTESTS=socketTests

all:	${SOCKETTESTS}

$(SOCKETTESTS) : $(SOCKETTESTSOBJFILES)
	$(CC) $(CFLAGS) $(SOCKETTESTSOBJFILES) -o $(SOCKETTESTS)

Client.o: ../../Client.hpp ../../Client.cpp
	$(CC) $(CFLAGS) -std=c++11 -c ../../Client.cpp	

Server.o: ../../Server.cpp ../../Server.hpp
	$(CC) $(CFLAGS) -c ../../Server.cpp

SocketTests.o: SocketTests.cpp
	$(CC) $(CFLAGS) -c SocketTests.cpp



remove:
	-rm -f *.o *.d *.exe 

clean:
	-rm -f *.o *.d *.exe *.gcov *.gcda *.gcno
	-rm -f ${SOCKETTESTS} ${GARBAGE}

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<