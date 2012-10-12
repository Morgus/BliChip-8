# Makefile
# Aleksi Blinnikka 8.10.2012-

# Directories
srcdir := source
objdir := obj
bindir := bin

# Build settings
CC = gcc
EXE = .exe
CFLAGS = -Wall -O2 -Iinclude -I/mingw/include/SDL2 -Dmain=SDL_main
LIBS = -L/mingw/lib -lmingw32 -lSDL2main -lSDL2 -mwindows

# Objects
OBJS := $(objdir)/main.o \
$(objdir)/CPU.o \
$(objdir)/memory.o \
$(objdir)/keyboard.o \
$(objdir)/display.o \
$(objdir)/opcodes.o

# Main build
all: $(OBJS)
	$(CC) $(OBJS) -o $(bindir)/BliChip8$(EXE) $(LIBS)

# Objects
$(objdir)/main.o: $(srcdir)/main.c
	$(CC) -c $? -o $@ $(CFLAGS)

$(objdir)/CPU.o: $(srcdir)/CPU.c
	$(CC) -c $? -o $@ $(CFLAGS)

$(objdir)/memory.o: $(srcdir)/memory.c
	$(CC) -c $? -o $@ $(CFLAGS)

$(objdir)/keyboard.o: $(srcdir)/keyboard.c
	$(CC) -c $? -o $@ $(CFLAGS)

$(objdir)/display.o: $(srcdir)/display.c
	$(CC) -c $? -o $@ $(CFLAGS)

$(objdir)/opcodes.o: $(srcdir)/opcodes.c
	$(CC) -c $? -o $@ $(CFLAGS)

clean:
	rm -f $(bindir)/*.exe
	rm -f $(objdir)/*
