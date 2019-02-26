CC	= gcc
CFLAGS 	= -g

all: oss user

oss:	oss.c
	$(CC) -o oss oss.c

user:	user.c
	$(CC) -o user user.c

.PHONY:	clean
clean:
	/bin/rm -f *.o *~ oss
	/bin/rm -f *.o *~ user
