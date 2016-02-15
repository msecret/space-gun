
export CC = g++
export LIBNAME = gaming.a
export XFLAGS = -Wall -g -std=c++11 `sdl2-config --cflags`
export SDL_LDFLAGS := $(shell sdl2-config --libs)
export LFLAGS = $(SDL_LDFLAGS)
export CFLAGS = $(XFLAGS)
VPATH = src
TARGET = space-gun

export DISTDIR := build

MAIN := src/main.cpp
OBJECTS := c_boundable.o c_evented.o c_moveable.o s_bound.o s_movement.o s_sdl_events.o
LIBS := $(LIBNAME)
DISTS := $(addprefix $(DISTDIR)/,$(OBJECTS))
LIBDISTS = $(addprefix $(DISTDIR)/,$(LIBS))

SUBDIRS = src/lib

$(DISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(DISTS) subdirs
	$(CC) $(CFLAGS) $(DISTS) $(MAIN) -o $(DISTDIR)/$@ $(LIBDISTS) $(LFLAGS)

$(OBJS): | $(DISTDIR)
$(DISTDIR):
	mkdir -p $(DISTDIR)


.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

clean:
	-@rm -rf build/* 2>/dev/null || true
