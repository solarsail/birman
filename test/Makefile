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

$(OUTDIR)/render-test: $(OBJDIR)/render-test.o $(OBJDIR)/map.o $(OBJDIR)/render.o $(COMPONENT_OBJ) $(OBJDIR)/position.o $(OBJDIR)/game.o
	$(LINK) -o $@ $^ $(LIBS)

$(OUTDIR)/sfml-test: $(OBJDIR)/sfml-test.o
	$(LINK) -o $@ $^ $(LIBS)

.PHONY: all
