CC = g++
CFLAGS = -Wall

OBJS = main.o barbearia.o
EXECS = trabalho2
ALL = $(EXECS)

all: $(ALL)

.c.o:
	$(CC) $(CFLAGS) -c $<

$(EXECS): $(OBJS)
	$(CC) $(CFLAGS) -o trabalho2 $(OBJS)

clean:
	rm -f *.o trabalho2