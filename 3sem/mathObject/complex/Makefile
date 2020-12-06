CC = g++ $(CFLAGS)
CFLAGS = -O0 -g

all: complexTst cubicEq

complexTst: Complex.h Complex.cpp complexTst.cpp
	$(CC) -o complexTst complexTst.cpp Complex.cpp

cubicEq: Complex.h cubicEq.cpp
	$(CC) -o cubicEq cubicEq.cpp

clean:
	rm -f complexTst
	rm -f cubicEq
