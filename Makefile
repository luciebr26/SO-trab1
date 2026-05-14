CC = gcc

CFLAGS = -Wall -Wextra -g

SRC = src/main.c \
      src/kernel.c \
      src/intercontroller.c \
      src/app.c

OBJ = $(SRC:.c=.o)

TARGET = kernel_sim

INCLUDES = -Iinclude

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)

re: clean all