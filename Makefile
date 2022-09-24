CC 			= gcc
TARGET 		= transform
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g
LIBFLAGS	= -lavcodec -lavformat -lswresample -lswscale -lavutil

VPATH 		= /$(realpath $(CURDIR)/../src/core/):/$(realpath $(CURDIR)/../src/libs/)

PROJDIR		= $(realpath $(CURDIR))
SRC 		= $(shell find $(PROJDIR)/src -name '*.c')
SRCDIR		= $(PROJDIR)/$(SRC)
LIBDIR		= $(PROJDIR)/include
OBJDIR		= $(PROJDIR)/bin
BUILDDIR 	= $(PROJDIR)/build


all: compile run 

compile: ${OBJS}
	${CC} ${CFLAGS} ${SRC} ${LIBFLAGS} -o $(TARGET) 

run:
	./${TARGET}

clean:
	rm -f $(SRCDIR/*.o) $(TARGET) *~

