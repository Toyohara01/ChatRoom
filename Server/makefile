INCLUDE_DIRS = 
LIB_DIRS = 
CC = g++

CDEFS=
CFLAGS= $(INCLUDE_DIRS) $(CDEFS)
OBJFILES = ATM.o operatorPanel.o Transaction.o Transfer.o Inquiry.o Withdrawal.o Deposit.o Session.o main.o
LIBS= 

PRODUCT=main

HFILES= ATM.hpp operatorPanel.hpp Transaction.hpp Transfer.hpp Transaction.hpp Inquiry.hpp Withdrawal.hpp Deposit.hpp Session.hpp
CFILES= ATM.cpp operatorPanel.cpp Transaction.cpp Transfer.cpp Transaction.cpp Inquiry.cpp Withdrawal.cpp Deposit.cpp Session.cpp main.cpp

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

$(PRODUCT) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(PRODUCT) $(OBJFILES) 

ATM.o: ATM.cpp ATM.hpp
	$(CC) $(CFLAGS) -c ATM.cpp

operatorPanel.o: operatorPanel.cpp operatorPanel.hpp
	$(CC) $(CFLAGS) -c operatorPanel.cpp

Transaction.o: Transaction.cpp Transaction.hpp
	$(CC) $(CFLAGS) -c Transaction.cpp

Transfer.o: Transfer.cpp Transfer.hpp
	$(CC) $(CFLAGS) -c Transfer.cpp

Inquiry.o: Inquiry.cpp Inquiry.hpp
	$(CC) $(CFLAGS) -c Inquiry.cpp

Withdrawal.o: Withdrawal.cpp Withdrawal.hpp
	$(CC) $(CFLAGS) -c Withdrawal.cpp

Deposit.o: Deposit.cpp Deposit.hpp
	$(CC) $(CFLAGS) -c Deposit.cpp

Session.o: Session.cpp Session.hpp
	$(CC) $(CFLAGS) -c Session.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp


clean:
	-rm -f *.o *.d *.exe 
	-rm -f ${PRODUCT} ${GARBAGE}


depend:

.c.o:
	$(CC) -MD $(CFLAGS) -c $<
