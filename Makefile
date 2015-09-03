# David Iacono - CSC 412 Spring 2014 - Makefile for sleeping TA
# 4/29/14 Project 3 Sleeping TA
CC=gcc
CFLAGS=-lpthread

all: sleeping_ta

sleeping_ta: main.o student.o ta.o
	$(CC) $(CFLAGS) -o sleeping_ta main.o student.o ta.o

main.o: main.c ta.h
	$(CC) $(CFLAGS) -c main.c

student.o: student.c ta.h
	$(CC) $(CFLAGS) -c student.c

ta.o: ta.c ta.h
	$(CC) $(CFLAGS) -lpthread -c ta.c
	
clean:
	rm sleeping_ta main.o student.o ta.o
