MAINPROG=Pente_Grammai_Simulator

SOURCES:=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(MAINPROG)

$(MAINPROG): $(OBJECTS)
	g++ $(OBJECTS) -o $@

.cpp.o:
	g++ -c $< -o $@

clean:
	rm *.o $(MAINPROG)
