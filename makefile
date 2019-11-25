all: ci ri main

main: main.o ops-num.o ops-str.o
	g++ main.o ops-num.o ops-str.o -o main

main.o:
	g++ -Wall -c main.cpp 

ci: createindex.o ops-num.o ops-str.o
	g++ createindex.o ops-num.o ops-str.o -o ci

createindex.o:
	g++ -Wall -c createindex.cpp

ops-num.o:
	g++ -Wall -c ops-num.cpp

ops-str.o:
	g++ -Wall -c ops-str.cpp

ri: readindex.o
	g++ readindex.o -o ri

readindex.o:
	g++ -Wall -c readindex.cpp

clean:
	rm ci ri main createindex.o ops-num.o ops-str.o readindex.o main.o 