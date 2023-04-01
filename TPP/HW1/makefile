CC = g++
CFLAGS = -Wall

OBJFILES = main.o maze.o robot.o
TARGET = main

DEPS = maze.h robot.h

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)
clean:
	rm -f $(OBJFILES) $(TARGET) *~