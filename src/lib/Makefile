
RDISTDIR = ../../$(DISTDIR)

OBJECTS := component.o entity.o positioning.o
DISTS = $(addprefix $(RDISTDIR)/,$(OBJECTS))

TARGET := $(LIBNAME)


$(RDISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(RDISTDIR)/$(TARGET): $(DISTS)
	@echo "Making shared lib: $(TARGET)"
	ar -rcs $@ $^

.PHONY: all
all: $(TARGET)

