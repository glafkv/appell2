CC	= gcc
CFLAGS	= -g
TARGET	= oss
OBJS	= oss.o user.o

$(TARGET): $(OBJS)
	   $(CC) -o $(TARGET) $(OBJS)

oss.o:	oss.c
	$(CC) $(CFLAGS) -c oss.c

user.o: user.c
	 $(CC) $(CFLAGS) -c user.c

.PHONY:	clean
clean:
	/bin/rm -f *.o $(TARGET)
