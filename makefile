all: ci ri main

main: main.o ops-id.o
	g++ main.o ops-id.o -o main

main.o:
	g++ -Wall -c main.cpp 

ci: createindex.o ops-id.o
	g++ createindex.o ops-id.o -o ci

createindex.o:
	g++ -Wall -c createindex.cpp

ops-id.o:
	g++ -Wall -c ops-id.cpp

ri: readindex.o
	g++ readindex.o -o ri

readindex.o:
	g++ -Wall -c readindex.cpp

clean:
	rm ci ri main createindex.o ops-id.o readindex.o main.o 