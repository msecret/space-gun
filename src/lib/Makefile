
RDISTDIR = $(DISTDIR)

OBJECTS := clock.o component.o entity.o event_emitter.o manager.o sdl_renderer.o units.o 
DISTS = $(addprefix $(RDISTDIR)/,$(OBJECTS))

TARGET := $(LIBNAME)


$(RDISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@ $(LFLAGS)

$(RDISTDIR)/$(TARGET): $(OBJECTS)
	@echo "Making shared lib: $(TARGET)"
	ar -rcs $@ $^

.PHONY: all
all: $(TARGET)

