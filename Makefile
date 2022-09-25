CC 			= gcc
TARGET 		= transform
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g
LIBFLAGS	= -lavcodec -lavformat -lswresample -lswscale -lavutil

VPATH 		= /$(realpath $(CURDIR)/../src/core/):/$(realpath $(CURDIR)/../src/libs/)

PROJDIR		= $(realpath $(CURDIR))

SRCDIR		= $(PROJDIR)/$(SRC)
#SRC 		= $(shell find $(PROJDIR)/src -name '*.c')
SRC			= $(PROJDIR)/src/vid/fdrad-001.c
LIBDIR		= $(PROJDIR)/include
# directory where object files will be stored
OBJDIR		= $(PROJDIR)/bin
OBJS		= fdrad-001.o
# directory to store main executable
BIN			= $(OBJDIR)/run
# DNE For now
BUILDDIR 	= $(PROJDIR)/build


all: compile run 

compile: ${OBJS}
	${CC} ${CFLAGS} ${SRC} ${LIBFLAGS} -o ${TARGET} 

run:
	./${TARGET}

clean:
	rm -f ${TARGET} ${OBJS}


