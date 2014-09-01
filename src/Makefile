OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(wildcard *.cpp))

$(OBJDIR)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -o $@ $<

all: $(OBJS) subsystem

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

subsystem:
	@$(MAKE) -C systems
	@$(MAKE) -C components

.PHONY: all subsystem
