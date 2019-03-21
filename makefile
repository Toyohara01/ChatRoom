INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall -pthread
CHATROOMOBJFILES = Server.o ChatRoom.o Message.o 
CHATWINDOWOBJFILES= ChatWindow.o Client.o Message.o
LIBS= 

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

CHATROOM=Chatroom
CHATWINDOW=Chatwindow

all:	${CHATROOM} $(CHATWINDOW)

$(CHATROOM) : $(CHATROOMOBJFILES)
	$(CC) $(CFLAGS) $(CHATROOMOBJFILES) -o $(CHATROOM) 

$(CHATWINDOW) : $(CHATWINDOWOBJFILES)
	$(CC) $(CFLAGS) $(CHATWINDOWOBJFILES) -o $(CHATWINDOW)

Enigma.o: Enigma.hpp Enigma.cpp
	$(CC) $(CFLAGS) -c Enigma.cpp

Archive.o: Archive.hpp Archive.cpp
	$(CC) $(CFLAGS) -c Archive.cpp

Client.o: Client.hpp Client.cpp
	$(CC) $(CFLAGS) -std=c++11 -c Client.cpp	

Server.o: Server.cpp Server.hpp
	$(CC) $(CFLAGS) -c Server.cpp

Message.o: Message.cpp Message.hpp
	$(CC) $(CFLAGS) -c Message.cpp

ChatRoom.o: ChatRoom.cpp
	$(CC) $(CFLAGS) -c ChatRoom.cpp

ChatWindow.o: ChatWindow.cpp
	$(CC) $(CFLAGS) -c ChatWindow.cpp

remove:
	-rm -f *.o *.d *.exe 

clean:
	-rm -f *.o *.d *.exe 
	-rm -f ${CHATROOM} ${CHATWINDOW} ${GARBAGE}

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
