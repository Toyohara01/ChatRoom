INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= $(INCLUDE_DIRS) $(CDEFS) -Wall -pthread --coverage -g
CHATROOMOBJFILES = Server.o ChatRoom.o Message.o ChatRoomMain.o
CHATWINDOWOBJFILES= ChatWindow.o Client.o Message.o ChatWindowMain.o Crypto.o Archive.o
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

Crypto.o: Crypto.hpp Crypto.cpp
	$(CC) $(CFLAGS) -std=c++11 -c Crypto.cpp

Archive.o: Archive.hpp Archive.cpp
	$(CC) $(CFLAGS) -c Archive.cpp

Client.o: Client.hpp Client.cpp
	$(CC) $(CFLAGS) -std=c++11 -c Client.cpp	

Server.o: Server.cpp Server.hpp
	$(CC) $(CFLAGS) -std=c++11 -c Server.cpp

Message.o: Message.cpp Message.hpp
	$(CC) $(CFLAGS) -std=c++11 -c Message.cpp

ChatRoom.o: ChatRoom.cpp ChatRoom.hpp
	$(CC) $(CFLAGS) -std=c++11 -c ChatRoom.cpp

ChatRoomMain.o: ChatRoomMain.cpp
	$(CC) $(CFLAGS) -std=c++11 -c ChatRoomMain.cpp

ChatWindow.o: ChatWindow.cpp ChatWindow.hpp
	$(CC) $(CFLAGS) -std=c++11 -c ChatWindow.cpp 

ChatWindowMain.o: ChatRoomMain.cpp
	$(CC) $(CFLAGS) -std=c++11 -c ChatWindowMain.cpp

remove:
	-rm -f *.o *.d *.exe 

clean:
	-rm -f *.o *.d *.exe *.gcov *.gcda *.gcno
	-rm -f ${CHATROOM} ${CHATWINDOW} ${GARBAGE}

depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
