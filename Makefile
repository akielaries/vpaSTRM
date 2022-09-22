CC 			= gcc
CFLAGS 		= -Wall -Wextra -g
VPATH 		= /$(realpath $(CURDIR)/../src/core/):/$(realpath $(CURDIR)/../src/libs/)
PROJDIR		= $(realpath $(CURDIR)/..)
SRCDIR 		:= $(shell find $(PROJDIR)/src -name '*.c')
BUILDDIR 	= $(PROJDIR)/build
# Do something about object files
TARGET 		= main
VERBOSE 	= TRUE

all: compile run 

compile:
	${CC} ${CFLAGS} ${SRCDIR} -o $(TARGET) 

run:
	./${TARGET}

clean:
	rm -f $(SRCDIR/*.o) $(TARGET) *~

