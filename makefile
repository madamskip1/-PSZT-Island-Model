all: main.o Evolution.o Population.o ConfigInterpreter.o Individual.o RandomNumber.o
	g++ main.o -g -o pszt Evolution.o Population.o ConfigInterpreter.o Individual.o RandomNumber.o

main.o: main.cpp
	g++ -c main.cpp 

Evolution.o: Evolution.cpp Evolution.h Population.o ConfigInterpreter.o
	g++ -c Evolution.cpp

Population.o: Population.cpp Population.h Individual.o
	g++ -c Population.cpp

ConfigInterpreter.o: ConfigInterpreter.cpp ConfigInterpreter.h
	g++ -c ConfigInterpreter.cpp

Individual.o: Individual.cpp Individual.h RandomNumber.o
	g++ -c Individual.cpp

RandomNumber.o: RandomNumber.cpp RandomNumber.h
	g++ -c RandomNumber.cpp


clean:
	rm -f *.o
	rm pszt 