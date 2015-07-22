
CC = g++
XFLAGS = -Wall -g
LFLAGS = -lSDL
TARGET = space-gun
LIBS = $(BUILDDIR)/entity.o \
			 $(BUILDDIR)/renderer.o \
			 $(BUILDDIR)/component.o
OBJS =

VPATH = src
SRCDIR := src
BUILDDIR := build
INCDIRS := -I /usr/include/SDL
LIBDIR := $(SRCDIR)/lib

MAIN := ${SRCDIR}/main.cpp

CFLAGS = ${XFLAGS} ${INCDIRS} ${LFLAGS}

all: $(OBJS)
	${CC} ${CFLAGS} $(MAIN) $(OBJS) -o $(BUILDDIR)/$(TARGET)

# Libs
$(BUILDDIR)/entity.o:
	${CC} ${CFLAGS} -c ${LIBDIR}/entity.cpp -o $(BUILDDIR)/entity.o

$(BUILDDIR)/renderer.o:
	${CC} ${CFLAGS} -c ${LIBDIR}/renderer.h -o $(BUILDDIR)/renderer.o

$(BUILDDIR)/component.o:
	${CC} ${CFLAGS} -c ${LIBDIR}/component.h -o $(BUILDDIR)/renderer.o

clean:
	-rm -r build/*
	rm -rf `find . -name "*.dSYM" -print`
