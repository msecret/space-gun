
ifndef GTEST_DIR
GTEST_DIR := /usr/include/gtest
endif
ifndef GMOCK_DIR
GMOCK_DIR := /usr/include/gmock
endif

LIBBOX2D = /usr/lib/libBox2D.a
export CC = g++
export LIBNAME = gaming.a
export XFLAGS = -Wall -g -std=c++11
export SDL_LDFLAGS := $(shell sdl2-config --static-libs)
export SDLTTF_LDFLAGS = -L/usr/lib -lSDL_ttf
export BOX2D_LDFLAGS := -L/usr/lib -Wl,-Bstatic -lBox2D -Wl,-Bdynamic
export BOX2D_INCFLAGS := -I/usr/include/Box2D
export LFLAGS = -lpthread $(BOX2D_LDFLAGS) $(SDL_LDFLAGS) $(SDLTTF_LDFLAGS)
export IFLAGS = $(BOX2D_INCFLAGS)
export CFLAGS = $(XFLAGS) $(LFLAGS)
VPATH = src

export DISTDIR := build
export RDISTDIR := ../../build
SRCDIR = src
TESTDIR = $(SRCDIR)/test
TARGET = $(DISTDIR)/space-gun
TEST = $(DISTDIR)/test_run

MAIN := src/main.cpp

HEADERS = $(shell find ./src -maxdepth 1 -name *.h)
SRCS=$(shell find ./src -maxdepth 1 -name *.cpp )
OBJS:=$(HEADERS:.h=.o)
OBJS:=$(subst $(SRCDIR),$(DISTDIR),$(OBJS))

LIBS := $(LIBNAME)
DISTS := $(addprefix $(DISTDIR)/,$(OBJS))
LIBDISTS = $(addprefix $(DISTDIR)/,$(LIBS))

GTEST_HEADERS = $(GTEST_DIR)/include
GMOCK_HEADERS = $(GMOCK_DIR)/include

LIBGTEST = /usr/lib/libgtest_main.so /usr/lib/libgtest.so
LIBGMOCK = /usr/lib/libgmock_main.so /usr/lib/libgmock.so

SUBDIRS = src/lib
COPY_FILES = $(DISTDIR)/DejaVuSansMono.ttf

$(DISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS) subdirs $(COPY_FILES)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN) -o $@ $(LIBDISTS) $(LIBBOX2D) $(LFLAGS)

$(TEST): $(OBJS) $(TESTDIR)/*.cpp $(LIBDISTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBGTEST) $(LIBGMOCK) $(LIBDISTS) $(LIBBOX2D) $(LFLAGS)
	./$(TEST)

$(OBJS): | $(DISTDIR)
$(DISTDIR):
	mkdir -p $(DISTDIR)

$(DISTDIR)/DejaVuSansMono.ttf: fonts/DejaVuSansMono.ttf
	cp -f $< $@

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

test: $(TEST)

clean:
	-@rm -rf build/* 2>/dev/null || true

print-%:
	@echo '$*=$($*)'
	@echo '   value = $(value  $*)'
