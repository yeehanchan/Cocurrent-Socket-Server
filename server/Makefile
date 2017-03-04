CC=gcc
CFLAGS=-I.
DEPS = parse.h y.tab.h httpResponse.h
OBJ = y.tab.o lex.yy.o parse.o server.o httpResponse.o
FLAGS = -g -Wall


default:all

all: server

lex.yy.c: lexer.l
	flex $^

y.tab.c: parser.y
	yacc -d $^

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c -o $@ $< $(CFLAGS)

server.c: $(OBJ)
	@gcc httpResponse.c -o httpResponse -Wall -Werror
	@gcc server.c -o server -Wall -Werror


clean:
	rm -f *~ *.o server lex.yy.c y.tab.c y.tab.h

