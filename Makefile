CC = gcc
LIBS = -I/usr/include/freetype2 -lfreetype
CFLAGS = -Wall -Wextra -ggdb $(LIBS)
TARGET = yoyo

yoyo: src/*
	$(CC) $(CFLAGS) src/*.c src/text/*.c -o $(TARGET)
