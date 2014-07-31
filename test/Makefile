all: entity-test
entity-test: entity-component-test.cpp ../src/entityfactory.cpp ../src/entity.cpp ../src/components/component.cpp
	g++ -g -std=c++11 -I../src/include -o ../bin/$@ $^
