
CFLAGS=-DUNIX -lreadline -lcurses -lgphoto2 
DEBUG=-g
#DEBUG=

all: shell


shell:	shell.c focus.c parse.c parse.h  context.c config.c samples.h
	gcc $(CFLAGS) $(DEBUG) -Wall focus.c shell.c parse.c  context.c config.c -o shell
clean:
	rm -f shell *~

