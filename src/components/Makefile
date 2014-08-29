OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(wildcard *.cpp))

$(OBJDIR)/%.o : %.cpp
	$(CC) $(CXXFLAGS) -o $@ $<

all: $(OBJS) subsystem

.PHONY: all subsystem
