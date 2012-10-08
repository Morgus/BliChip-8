# Makefile
# Aleksi Blinnikka 8.10.2012-

# Directories
srcdir := source
objdir := obj
bindir := bin

# Build settings
CC = gcc
EXE = .exe
CFLAGS = -Wall -W -O2 -Iinclude

# Objects
OBJS := $(objdir)/main.o \
$(objdir)/CPU.o \
$(objdir)/memory.o \
$(objdir)/keyboard.o

# Main build
all: $(OBJS)
	$(CC) $(OBJS) -o $(bindir)/program$(EXE)

# Objects
$(objdir)/main.o: $(srcdir)/main.c
	$(CC) -c $? -o $@ $(CFLAGS)

$(objdir)/CPU.o: $(srcdir)/CPU.c
	$(CC) -c $? -o $@ $(CFLAGS)

$(objdir)/memory.o: $(srcdir)/memory.c
	$(CC) -c $? -o $@ $(CFLAGS)

$(objdir)/keyboard.o: $(srcdir)/keyboard.c
	$(CC) -c $? -o $@ $(CFLAGS)

clean:
	rm -f $(bindir)/program.exe
	rm -f $(objdir)/*
