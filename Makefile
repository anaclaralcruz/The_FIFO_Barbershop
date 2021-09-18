#CC = g++
#CFLAGS = -Wall
#LDFLAGS = -pthread

#OBJS = main.o
#EXECS = trabalho2
#ALL = $(EXECS)

#all: $(ALL)

#.c.o:
#	$(CC) $(CFLAGS) -c $<

#$(EXECS): $(OBJS)
#	$(CC) $(CFLAGS) -o trabalho2 $(OBJS)

#clean:
#	rm -f *.o trabalho2

# the compiler
CC = gcc

# compiler flags:
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -Werror -D_POSIX_THREAD_SEMANTICS
LDFLAGS = -pthread

# the build target executable:
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDFLAGS)

clean:
	$(RM) $(TARGET)