
CC = g++
XFLAGS = -Wall -g
LFLAGS = -lSDL
TARGET = space-gun
OBJS = $(BUILDDIR)/entity.o \
			 $(BUILDDIR)/renderer.o \
			 $(BUILDDIR)/component/component.o

VPATH = src
SRCDIR := src
BUILDDIR := build
INCDIRS := -I /usr/include/SDL

MAIN := ${SRCDIR}/main.cpp

CFLAGS = ${XFLAGS} ${INCDIRS} ${LFLAGS}

all: $(OBJS)
	${CC} ${CFLAGS} $(MAIN) $(OBJS) -o $(BUILDDIR)/$(TARGET)

$(BUILDDIR)/entity.o:
	${CC} ${CFLAGS} -c ${SRCDIR}/entity.cpp -o $(BUILDDIR)/entity.o

$(BUILDDIR)/renderer.o:
	${CC} ${CFLAGS} -c ${SRCDIR}/renderer.h -o $(BUILDDIR)/renderer.o

$(BUILDDIR)/component.o:
	${CC} ${CFLAGS} -c ${SRCDIR}/component.h -o $(BUILDDIR)/renderer.o

clean:
	-rm -r build/*
	rm -rf `find . -name "*.dSYM" -print`
