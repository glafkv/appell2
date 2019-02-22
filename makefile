CC	= gcc
CFLAGS	= -g
TARGET	= oss
OBJS	= oss.o timer.o

$(TARGET): $(OBJS)
	   $(CC) -o $(TARGET) $(OBJS)

oss.o:	oss.c
	$(CC) $(CFLAGS) -c oss.c

timer.o: timer.c
	 $(CC) $(CFLAGS) -c timer.c

.PHONY:	clean
clean:
	/bin/rm -f *.o $(TARGET)
