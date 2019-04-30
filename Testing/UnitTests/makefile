INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
PFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall -g
CFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall -g --coverage
SOCKETTESTSOBJFILES = Server.o Client.o SocketTests.o
ENIGMATESTOBJFILES = Crypto.o enigmaTest.o
ARCHIVETESTOBJFILES = Archive.o ArchiveTest.o
LIBS= 

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

SOCKETTESTS=socketTests
ENIGMATEST=enigmaTest
ARCHIVETEST=ArchiveTest

all:	${SOCKETTESTS} ${ENIGMATEST} ${ARCHIVETEST}

$(SOCKETTESTS) : $(SOCKETTESTSOBJFILES)
	$(CC) $(CFLAGS) $(SOCKETTESTSOBJFILES) -o $(SOCKETTESTS)

Client.o: ../../Client.hpp ../../Client.cpp
	$(CC) $(CFLAGS) -std=c++11 -c ../../Client.cpp	

Server.o: ../../Server.cpp ../../Server.hpp
	$(CC) $(CFLAGS) -std=c++11 -c ../../Server.cpp

SocketTests.o: SocketTests.cpp
	$(CC) $(CFLAGS) -std=c++11 -c SocketTests.cpp

$(ENIGMATEST) : $(ENIGMATESTOBJFILES)
	$(CC) $(CFLAGS) $(ENIGMATESTOBJFILES) -o $(ENIGMATEST)

Crypto.o: ../../Crypto.hpp ../../Crypto.cpp
	$(CC) $(CFLAGS) -std=c++11 -c ../../Crypto.cpp

enigmaTest.o: enigmaTest.cpp
	$(CC) $(CFLAGS) -std=c++11 -c enigmaTest.cpp

$(ARCHIVETEST) : $(ARCHIVETESTOBJFILES)
	$(CC) $(CFLAGS) $(ARCHIVETESTOBJFILES) -o $(ARCHIVETEST)

Archive.o: ../../Archive.hpp ../../Archive.cpp
	$(CC) $(CFLAGS) -c ../../Archive.cpp

ArchiveTest.o: ArchiveTest.cpp
	$(CC) $(CFLAGS) -c ArchiveTest.cpp

remove:
	-rm -f *.o *.d *.exe 

clean:
	-rm -f *.o *.d *.exe *.gcov *.gcda *.gcno
	-rm -f ${SOCKETTESTS} ${ARCHIVETEST} ${ENIGMATEST} ${GARBAGE}

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<