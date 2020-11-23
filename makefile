all: main.o Evolution.o Population.o ConfigInterpreter.o Individual.o RandomNumber.o
	g++ ${FLAGS} main.o -g -o pszt Evolution.o Population.o ConfigInterpreter.o Individual.o RandomNumber.o

main.o: main.cpp
	g++ ${FLAGS} -c main.cpp 

Evolution.o: Evolution.cpp Evolution.h Population.o ConfigInterpreter.o
	g++ ${FLAGS} -c Evolution.cpp

Population.o: Population.cpp Population.h Individual.o
	g++ ${FLAGS} -c Population.cpp

ConfigInterpreter.o: ConfigInterpreter.cpp ConfigInterpreter.h
	g++ ${FLAGS} -c ConfigInterpreter.cpp

Individual.o: Individual.cpp Individual.h RandomNumber.o
	g++ ${FLAGS} -c Individual.cpp

RandomNumber.o: RandomNumber.cpp RandomNumber.h
	g++ ${FLAGS} -c RandomNumber.cpp


clean:
	rm -f *.o
	rm pszt 

FLAGS= -std=c++1z