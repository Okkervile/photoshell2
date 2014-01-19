
CFLAGS=-DUNIX -lreadline -lcurses -lgphoto2 
DEBUG=-g
#DEBUG=

all: shell


shell:	shell.c focus.c parse.c parse.h  context.c config.c samples.h iso.c
	gcc $(CFLAGS) $(DEBUG) -Wall focus.c context.c shell.c parse.c   config.c iso.c -o shell
clean:
	rm -f shell *~

