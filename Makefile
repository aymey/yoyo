CC = gcc
CFLAGS = -Wall -Wextra -ggdb
TARGET = yoyo

yoyo: src/*
	$(CC) $(CFLAGS) src/* -o $(TARGET)
