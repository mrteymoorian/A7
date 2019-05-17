all: a.out

a.out: main.o Network.o Customer.o Person.o Publisher.o Film.o
	g++ -std=c++11 main.o Network.o Customer.o Person.o Publisher.o Film.o -o a.out

main.o: main.cpp Network.h Customer.h Person.h Publisher.h Film.h Exception.h
	g++ -std=c++11 -c main.cpp

Person.o: Person.cpp Exception.h
	g++ -std=c++11 -c Person.cpp

Customer.o: Customer.cpp Person.h Film.h Exception.h
	g++ -std=c++11 -c Customer.cpp

Publisher.o: Publisher.cpp Person.h Film.h Exception.h
	g++ -std=c++11 -c Publisher.cpp

Network.o: Network.cpp Person.h Film.h Customer.h Publisher.h Exception.h
	g++ -std=c++11 -c Network.cpp

.PHONY: clean
clean:
	rm *.o
	rm a.out