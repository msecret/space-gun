
RDISTDIR = ../../$(DISTDIR)

OBJECTS := component.o entity.o positioning.o
DISTS := $(addprefix $(RDISTDIR)/,$(OBJECTS))

TARGET := $(LIBNAME)


$(RDISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(RDISTDIR)/$(TARGET): $(DISTS)
	ar -rcs $@.a $<
	$(CC) -m32 prog.o -L. -lmylib

.PHONY: all
all: $(TARGET)

