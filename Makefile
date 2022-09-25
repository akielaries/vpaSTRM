.SUFFIXES:
.SUFFIXES: .c .o
vpath %.c src
vpath %.o src

CC 			= gcc
TARGET 		= transform
VERBOSE 	= TRUE

CFLAGS 		= -Wall -Wextra -g
LIBFLAGS	= -lavcodec -lavformat -lswresample -lswscale -lavutil

PROJDIR		= $(realpath $(CURDIR))

SRCDIR		= $(PROJDIR)/src/vid
#SRC 		= $(shell find $(PROJDIR)/src -name '*.c')
#SRC			= $(PROJDIR)/src/vid/fdrad-001.c
SRC			= $(SRCDIR)/ *.c
LIBDIR		= $(PROJDIR)/include

# directory where object files will be stored
OBJDIR		= $(PROJDIR)/bin
# create objects from respective .c files
OBJS		= fdrad-001.o
# add object directory as prefix to our created object files
OBJS_PRE	= $(addprefix $(OBJDIR)/, $(OBJS))

# directory to store main executable
BIN			= $(OBJDIR)/run
# DNE For now
BUILDDIR 	= $(PROJDIR)/build


all: compile run 


compile: ${OBJS_PRE}
	#${CC} ${CFLAGS} ${SRC} ${LIBFLAGS} -o ${TARGET} 
	${CC} ${CFLAGS} ${LIBFLAGS} -o ${TARGET} ${OBJS_PRE}

	$(OBJDIR)/%.o : %.c 
		${CC} -c ${CFLAGS} $< -o $@


run:
	./${TARGET}


clean:
	rm -f ${TARGET} ${OBJS}


