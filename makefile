INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall
OBJFILES = Server.o Chatroom.o Chatwindow.o Enigma.o Message.o Client.o Archive.o
LIBS= 

PRODUCT=chatroom chatwindow

HFILES= Server.hpp Enigma.hpp Client.hpp Message.hpp
CFILES= Server.cpp Enigma.cpp Client.cpp Message.cpp

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT} ${PRODUCT1}

$(PRODUCT) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(OBJFILES) 

Enigma.o: Enigma.hpp Enigma.cpp
	$(CC) $(CFLAGS) -c Enigma.cpp

Archive.o: Archive.hpp Archive.cpp
	$(CC) $(CFLAGS) -c Archive.cpp

Client.o: Client.hpp Client.cpp
	$(CC) $(CFLAGS) -c Client.cpp	

Server.o: Server.cpp Server.hpp
	$(CC) $(CFLAGS) -c Server.cpp

Chatroom.o: ChatRoom.cpp
	$(CC) $(CFLAGS) -c ChatRoom.cpp

Chatwindow.o: ChatWindow.cpp
	$(CC) $(CFLAGS) -c ChatWindow.cpp

chatwindow: ${OBJS} Chatwindow.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) Chatwindow.o $(LIBS)

chatroom: ${OBJS} Chatroom.o
	$(CC) $(CFLAGS) -o $@ $(OBJS) Chatroom.o $(LIBS)

clean:
	-rm -f *.o *.d *.exe 
	-rm -f ${PRODUCT} ${GARBAGE}


depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
