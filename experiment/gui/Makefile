CC 			= gcc
CFLAGS 		= -Wall -Wextra -g 
SFLAGS		= -lncurses
VPATH 		= /$(realpath $(CURDIR)/../src/core/):/$(realpath $(CURDIR)/../src/libs/)
PROJDIR		= $(realpath $(CURDIR)/..)
# SRCDIR 		:= $(shell find $(PROJDIR)/src -name '*.c')
SRC			= ncurses-001.c
BUILDDIR 	= $(PROJDIR)/build
BINS		= main
# Do something about object files
OBJS		= ncurses-001.o
TARGET 		= main
VERBOSE 	= TRUE

all: compile run 

compile: ${OBJS}
	${CC} ${CFLAGS} ${SRC} ${SFLAGS} -o $(TARGET) 

run:
	./${TARGET}

clean:
	rm -f ${BINS} *.o

