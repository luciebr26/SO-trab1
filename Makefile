CC = gcc
CFLAGS = -Wall -Wextra

TARGET = main
SRCS = main.c app.c intercontroller.c kernel.c queue.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)