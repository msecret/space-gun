
export CC = g++
export LIBNAME = gaming
export XFLAGS = -Wall -g
export LFLAGS = -lSDL -lLIBNAME
VPATH = src
TARGET = space-gun

export DISTDIR := build

MAIN := src/main.cpp
OBJECTS := ball.o moveable.o
DISTS := $(addprefix $(DISTDIR)/,$(OBJECTS))

SUBDIRS = src/lib

$(DISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(DISTS) subdirs
	$(CC) $(CFLAGS) $(DISTS) $(MAIN) -o $(DISTDIR)/$@

$(OBJS): | $(DISTDIR)
$(DISTDIR):
	mkdir -p $(DISTDIR)


.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

clean:
	-@rm -rf build/* 2>/dev/null || true
