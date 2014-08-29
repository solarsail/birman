OUTDIR=../bin/
all: $(OUTDIR)sfml-test $(OUTDIR)entity-test $(OUTDIR)map-test $(OUTDIR)command-test
$(OUTDIR)entity-test: entity-component-test.cpp ../src/entityfactory.cpp ../src/entity.cpp ../src/components/component.cpp ../src/category.cpp
	g++ -g -std=c++11 -I../src/include -o $@ $^
$(OUTDIR)command-test: entity-command-test.cpp ../src/entityfactory.cpp ../src/entity.cpp ../src/components/component.cpp ../src/systems/command.cpp ../src/category.cpp
	g++ -g -std=c++11 -I../src/include -o $@ $^
$(OUTDIR)map-test: map-test.cpp ../src/systems/map.cpp
	g++ -g -std=c++11 -o $@ $^ -I../src/include -lsfml-graphics -lsfml-window -lsfml-system
$(OUTDIR)sfml-test: sfml-test.cpp
	g++ -g -std=c++11 -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system
