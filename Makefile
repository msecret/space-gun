
ifndef GTEST_DIR
GTEST_DIR := $(HOME)/Dev/googletest/googletest
endif
ifndef GMOCK_DIR
GMOCK_DIR := $(HOME)/Dev/googletest/googlemock
endif

export CC = g++
export LIBNAME = gaming.a
export XFLAGS = -Wall -g -std=c++11 `sdl2-config --cflags`
export SDL_LDFLAGS := $(shell sdl2-config --libs)
export LFLAGS = $(SDL_LDFLAGS)
export CFLAGS = $(XFLAGS)
VPATH = src

export DISTDIR := build
export RDISTDIR := ../../build
SRCDIR = src
TESTDIR = $(SRCDIR)/test
TARGET = $(DISTDIR)/space-gun
TEST = $(DISTDIR)/test_run

MAIN := src/main.cpp

HEADERS = $(shell find ./src -name *.h -maxdepth 1)
SRCS=$(shell find ./src -name *.cpp -maxdepth 1)
OBJS:=$(HEADERS:.h=.o)
OBJS:=$(subst $(SRCDIR),$(DISTDIR),$(OBJS))

LIBS := $(LIBNAME)
DISTS := $(addprefix $(DISTDIR)/,$(OBJS))
LIBDISTS = $(addprefix $(DISTDIR)/,$(LIBS))

GTEST_HEADERS = $(GTEST_DIR)/include

GMOCK_HEADERS = $(GMOCK_DIR)/include

LIBGTEST = /usr/local/lib/libgtest_main.a /usr/local/lib/libgtest.a
LIBGMOCK = /usr/local/lib/libgmock_main.a /usr/local/lib/libgmock.a

SUBDIRS = src/lib

$(DISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS) subdirs
	$(CC) $(CFLAGS) $(OBJS) $(MAIN) -o $@ $(LIBDISTS) $(LFLAGS)

$(TEST): $(OBJS) $(LIBDISTS)
	$(CC) $(CFLAGS) -o $@ $^ -I $(GTEST_HEADERS) -I $(GMOCK_HEADERS) $(TESTDIR)/*.cpp $(LIBGTEST) $(LIBGMOCK) $(LIBDISTS) $(LFLAGS)
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
