CC = g++
CFLAGS = -Wall -Wextra  -std=c++17 -O3 #-g -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS =-lraylib -lm
TARGET = main
SCRIPT_DIR = ../angelscript


SOURCES = main.cpp


INCLUDES = -I$(SCRIPT_DIR)/include


LIBS = -L$(SCRIPT_DIR)/lib -langelscript

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(SOURCES) $(LIBS) $(LDFLAGS)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
