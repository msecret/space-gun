
ifndef GTEST_DIR
GTEST_DIR := /usr/include/gtest
endif
ifndef GMOCK_DIR
GMOCK_DIR := /usr/include/gmock
endif

export CC = g++
export LIBNAME = gaming.a
export XFLAGS = -Wall -g -std=c++11 `sdl2-config --cflags`
export SDL_LDFLAGS := $(shell sdl2-config --libs)
export BOX2D_LDFLAGS := -I/usr/include/Box2D
export LFLAGS = -lpthread $(SDL_LDFLAGS)
export CFLAGS = $(XFLAGS)
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

LIBGTEST = /usr/lib/libgtest_main.a /usr/lib/libgtest.a
LIBGMOCK = /usr/lib/libgmock_main.a /usr/lib/libgmock.a
LIBBOX2D = /usr/lib/libBox2D.a

SUBDIRS = src/lib

$(DISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS) subdirs
	$(CC) $(CFLAGS) $(OBJS) $(MAIN) -o $@ $(LIBDISTS) $(LIBBOX2D) $(LFLAGS)

$(TEST): $(OBJS) $(TESTDIR)/*.cpp $(LIBDISTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBGTEST) $(LIBGMOCK) $(LIBDISTS) $(LIBBOX2D) $(LFLAGS)
	./$(TEST)

$(OBJS): | $(DISTDIR)
$(DISTDIR):
	mkdir -p $(DISTDIR)


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
