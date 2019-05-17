all: a.out

a.out: main.o Network.o Customer.o Person.o Publisher.o Film.o
	g++ -std=c++11 main.o Network.o Customer.o Person.o Publisher.o Film.o -o a.out

main.o: main.cpp Network.h Customer.h Person.h Publisher.h Film.h Exception.h
	g++ -std=c++11 -c -g main.cpp

Person.o: Person.cpp Exception.h Film.h
	g++ -std=c++11 -c -g Person.cpp

Customer.o: Customer.cpp Person.h Film.h Exception.h
	g++ -std=c++11 -c -g Customer.cpp

Publisher.o: Publisher.cpp Person.h Film.h Exception.h
	g++ -std=c++11 -c -g Publisher.cpp

Film.o: Film.cpp Person.h Publisher.h Customer.h
	g++ -std=c++11 -c -g Film.cpp

Network.o: Network.cpp Person.h Film.h Customer.h Publisher.h Exception.h
	g++ -std=c++11 -c -g Network.cpp

.PHONY: clean
clean:
	rm *.o
	rm a.out