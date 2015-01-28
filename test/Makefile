OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(wildcard *.cpp))
COMPONENT_OBJ := $(addprefix $(OBJDIR)/, entityfactory.o entity.o component.o command.o category.o eventkey.o)
TARGETS := $(addprefix $(OUTDIR)/, sfml-test entity-test map-test command-test render-test conf-test tgui-test)
LINK := g++

$(OBJDIR)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -o $@ $<

all: $(TARGETS)

$(OUTDIR)/entity-test: $(OBJDIR)/entity-component-test.o $(OBJDIR)/utility.o $(COMPONENT_OBJ)
	$(LINK) -o $@ $^

$(OUTDIR)/command-test: $(OBJDIR)/entity-command-test.o $(OBJDIR)/utility.o $(COMPONENT_OBJ)
	$(LINK) -o $@ $^

$(OUTDIR)/map-test: $(OBJDIR)/map-test.o $(OBJDIR)/map.o
	$(LINK) -o $@ $^ $(LIBS)

$(OUTDIR)/render-test: $(addprefix $(OBJDIR)/, animation.o render-test.o map.o render.o position.o animated-sprite.o movable.o game.o utility.o) $(COMPONENT_OBJ) 
	$(LINK) -o $@ $^ $(LIBS)

$(OUTDIR)/sfml-test: $(OBJDIR)/sfml-test.o
	$(LINK) -o $@ $^ $(LIBS)

$(OUTDIR)/conf-test: $(OBJDIR)/conf-test.o
	$(LINK) -o $@ $^ -lconfig++
$(OUTDIR)/tgui-test: $(OBJDIR)/tgui-test.o
	$(LINK) -o $@ $^ -ltgui  -lsfml-graphics -lsfml-window -lsfml-system
.PHONY: all
