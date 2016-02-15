
RDISTDIR = ../../$(DISTDIR)

OBJECTS := clock.o component.o entity.o event_emitter.o manager.o renderer.o sdl_renderer.o system.o units.o
DISTS = $(addprefix $(RDISTDIR)/,$(OBJECTS))

TARGET := $(LIBNAME)


$(RDISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@ $(LFLAGS)

$(RDISTDIR)/$(TARGET): $(DISTS)
	@echo "Making shared lib: $(TARGET)"
	ar -rcs $@ $^

.PHONY: all
all: $(TARGET)

