
RDISTDIR = ../../$(DISTDIR)

OBJECTS := component.o entity.o positioning.o
DISTS := $(addprefix $(RDISTDIR)/,$(OBJECTS))


$(RDISTDIR)/%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

all: $(DISTS)
	@echo $(DISTS)
