#.SUFFIXES:
#.SUFFIXES: .c .o
#vpath %.c src
#vpath %.o src

# define our project director
PROJDIR     = $(realpath $(CURDIR))

CC 			= gcc
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g
LFLAGS		= -lavcodec -lavformat -lswresample -lswscale -lavutil

SRCDIR		= $(PROJDIR)/src/
SRC 		= $(shell find $(PROJDIR)/src/v110 -name '*.c')
#SRC			= $(SRCDIR)/fdrad-001_LOGGER.c
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
TARGET 		= vpaSTRM-110
# store compiled binary in /bin/run
STORE_BIN	= $(addprefix $(BIN)/, $(TARGET))
LOG_FILES 	= $(shell find $(PROJDIR)/logs/ -name '*.txt')


all: compile run 


compile: 
	${CC} ${CLFAGS} ${SRC} ${LFLAGS} -o ${STORE_BIN}


run:
	# use var as an argument parser type function for our
	# compile-run.sh script
	./bin/run/convert-001 ${var}


clean:
	rm -f ${STORE_BIN} ${OBJS}
	# cd cv-data/output/tests && rm *.pgm


clean-imgs:
	rm cv-data/output/tests/*.pgm

clean-logs:
	rm -f ${LOG_FILES}

clean-all: 
	rm -f ${STORE_BIN} ${OBJS}
	rm -f cd-data/output/tests/*.pgm
	rm -f ${LOG_FILES}

