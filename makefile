# SHELL PATH and FILE SUFFIXES used in the compiling process
SHELL = /bin/sh
.SUFFIXES: .c .o

# COMPILER AND COMPILER FLAGS
CC = gcc
CFLAGS = -Wall -Werror

# SOURCE FILES, HEADER FILES
INCDIR = include
LIBDIR = src

INC = -Iinclude		# let gcc know where to look for .h files included (#include)

HEADERS = $(wildcard $(INCDIR)/*.h)
SRCFILES = $(wildcard $(LIBDIR)/*.c) $(TARGET).c
OBJFILES = $(SRCFILES:.c=.o)

# TARGET OUTPUT
TARGET = automata

DEBUG =

# to make it verbose, add VERBOSE=1 to the make command
ifndef VERBOSE
.SILENT:
endif

# MAKE RULES
# left depends on right
# $@ = The file name of the target of the rule
# $< = first thing on the right
# $^ = everything on the right

# any changes to .c files or .h files will lead to recompiling the whole thing
%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INC) $< -c -o $@


all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $@
	rm -f $(OBJFILES)

debug: CFLAGS += -g	# target specific var for debug
debug: $(OBJFILES)
	$(CC) $(CFLAGS) $^ -o $(TARGET)
	rm -f $(OBJFILES)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	rm -f $(OBJFILES)

# print header, source, object files used to the terminal
files:
	@echo Headers: $(HEADERS)
	@echo Source: $(SRCFILES)
	@echo Objects: $(OBJFILES)
