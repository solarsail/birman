OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(wildcard *.cpp))
COMPONENT_OBJ := $(addprefix $(OBJDIR)/, entityfactory.o entity.o component.o command.o category.o)
TARGETS := $(addprefix $(OUTDIR)/, sfml-test entity-test map-test command-test render-test)
LINK := g++

$(OBJDIR)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -o $@ $<

all: $(TARGETS)

$(OUTDIR)/entity-test: $(OBJDIR)/entity-component-test.o $(COMPONENT_OBJ)
	$(LINK) -o $@ $^

$(OUTDIR)/command-test: $(OBJDIR)/entity-command-test.o $(COMPONENT_OBJ)
	$(LINK) -o $@ $^

$(OUTDIR)/map-test: $(OBJDIR)/map-test.o $(OBJDIR)/map.o
	$(LINK) -o $@ $^ $(LIBS)

$(OUTDIR)/render-test: $(addprefix $(OBJDIR)/, animation.o render-test.o map.o render.o position.o animated-sprite.o movable.o game.o utility.o eventkey.o command.o) $(COMPONENT_OBJ) 
	$(LINK) -o $@ $^ $(LIBS)

$(OUTDIR)/sfml-test: $(OBJDIR)/sfml-test.o
	$(LINK) -o $@ $^ $(LIBS)

.PHONY: all
