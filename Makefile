CC 			= gcc
TARGET 		= transform
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g
LIBFLAGS	= -lavcodec -lavformat -lswresample -lswscale -lavutil

VPATH 		= /$(realpath $(CURDIR)/../src/core/):/$(realpath $(CURDIR)/../src/libs/)

PROJDIR		= $(realpath $(CURDIR))
SRCDIR		= $(PROJDIR)/$(SRC)
#SRC 		= $(shell find $(PROJDIR)/src -name '*.c')
SRC			= $(PROJDIR)/src/vid
LIBDIR		= $(PROJDIR)/include
OBJDIR		= $(PROJDIR)/bin
OBJS		= fdrad-001.o
BUILDDIR 	= $(PROJDIR)/build


all: compile run 

compile: ${OBJS}
	${CC} ${CFLAGS} ${SRC} ${LIBFLAGS} -o $(TARGET) 

run:
	./${TARGET}

clean:
	rm -f ${TARGET} ${OBJS}

