PROGRAM = izvrsni
CC = g++
CFLAGS = -Wall -ansi

$(PROGRAM) : regex.o stanje.o prelaz.o automat.o main.o
	$(CC) -o $(PROGRAM) $^

main.o : main.cpp regex.h
	$(CC) -c $(CFLAGS) $<

regex.o : regex.cpp regex.h
	$(CC) -c $(CFLAGS) $<


stanje.o : stanje.cpp stanje.h
	$(CC) -c $(CFLAGS) $<


prelaz.o : prelaz.cpp prelaz.h
	$(CC) -c $(CFLAGS) $<


automat.o : automat.cpp automat.h
	$(CC) -c $(CFLAGS) $<




.PHONY: clean


clean:
	rm *.o $(PROGRAM) *~ *# 




