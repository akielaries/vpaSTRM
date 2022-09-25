.SUFFIXES:
.SUFFIXES: .c .o
vpath %.c src
vpath %.o src

# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC 			= gcc
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g
LFLAGS		= -lavcodec -lavformat -lswresample -lswscale -lavutil

SRCDIR		= $(PROJDIR)/src/vid
SRC 		= $(shell find $(PROJDIR)/src/vid -name '*.c')
LIBDIR		= $(PROJDIR)/include

# directory where object files will be stored
OBJDIR		= $(PROJDIR)/bin
# create objects from respective .c files
# OBJS		= fdrad-001.o
# add object directory as prefix to our created object files
# OBJS_PRE	= $(addprefix $(OBJDIR)/, $(OBJS))

# directory to store main executable
BIN			= $(OBJDIR)/run
# DNE For now
BUILDDIR 	= $(PROJDIR)/build

# compiled binary
TARGET 		= transform-002
# store compiled binary in /bin/run
STORE_BIN	= $(addprefix $(BIN)/, $(TARGET))


all: compile run 


compile: 
	${CC} ${CLFAGS} ${SRC} ${LFLAGS} -o ${STORE_BIN}


run:
	# ./bin/run/transform-002 ${ARGS} 
	# use var as an argument parser type function for our
	# compile-run.sh script
	./bin/run/transform-002 ${var}


clean:
	rm -f ${STORE_BIN} ${OBJS}


