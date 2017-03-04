CC=gcc
CFLAGS=-I.
DEPS = httpResponse.h parse.h y.tab.h
OBJ = y.tab.o lex.yy.o httpResponse.o parse.o server.o
FLAGS = -g -Wall

default:all

all: server run

lex.yy.c: lexer.l
	flex $^

y.tab.c: parser.y
	yacc -d $^

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *~ *.o server lex.yy.c y.tab.c y.tab.h

run:	server
	./server
