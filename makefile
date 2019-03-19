INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall
CHATROOMOBJFILES = Server.o Chatroom.o Message.o Archive.o
CHATWINDOWOBJFILES= Chatwindow.o Client.o Message.o  Archive.o
LIBS= 

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

CHATROOM=Chatroom
CHATWINDOW=Chatwindow

all:	${CHATROOM} $(CHATWINDOW) ${remove}

$(CHATROOM) : $(CHATROOMOBJFILES)
	$(CC) $(CFLAGS) $(CHATROOMOBJFILES) -o $(CHATROOM) 

$(CHATWINDOW) : $(CHATWINDOWOBJFILES)
	$(CC) $(CFLAGS) $(CHATWINDOWOBJFILES) -o $(CHATWINDOW)

Enigma.o: Enigma.hpp Enigma.cpp
	$(CC) $(CFLAGS) -c Enigma.cpp

Archive.o: Archive.hpp Archive.cpp
	$(CC) $(CFLAGS) -c Archive.cpp

Client.o: Client.hpp Client.cpp
	$(CC) $(CFLAGS) -c Client.cpp	

Server.o: Server.cpp Server.hpp
	$(CC) $(CFLAGS) -c Server.cpp

Message.o: Message.cpp Message.hpp
	$(CC) $(CFLAGS) -c Message.cpp

Chatroom.o: ChatRoom.cpp
	$(CC) $(CFLAGS) -c ChatRoom.cpp

Chatwindow.o: ChatWindow.cpp
	$(CC) $(CFLAGS) -c ChatWindow.cpp

remove:
	-rm -f *.o *.d *.exe 

clean:
	-rm -f *.o *.d *.exe 
	-rm -f ${CHATROOM} ${CHATWINDOW} ${GARBAGE}


depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
