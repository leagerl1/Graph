COMP=g++ -std=c++0x
EXE1=lab11
FLAGS=-g

all: Driver.o Graph.o
	$(COMP) $(FLAGS) Driver.o Graph.o -o $(EXE1)

Driver.o: Driver.cpp
	$(COMP) $(FLAGS) -c Driver.cpp

Graph.o: Graph.cpp
	$(COMP) $(FLAGS) -c Graph.cpp

clean:
	rm -rf *.o *.gch *.a $(EXE1)
