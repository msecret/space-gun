
export CC = g++
export LIBNAME = gaming.a
export XFLAGS = -Wall -g -std=c++11
export LFLAGS = -lSDL
export CFLAGS = $(XFLAGS) $(LFLAGS)
VPATH = src
TARGET = space-gun

export DISTDIR := build

MAIN := src/main.cpp
OBJECTS := ball.o moveable.o
LIBS := $(LIBNAME)
DISTS := $(addprefix $(DISTDIR)/,$(OBJECTS))
LIBDISTS = $(addprefix $(DISTDIR)/,$(LIBS))

SUBDIRS = src/lib

$(DISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(DISTS) subdirs
	$(CC) $(CFLAGS) $(DISTS) $(MAIN) -o $(DISTDIR)/$@ $(LIBDISTS)

$(OBJS): | $(DISTDIR)
$(DISTDIR):
	mkdir -p $(DISTDIR)


.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

clean:
	-@rm -rf build/* 2>/dev/null || true
