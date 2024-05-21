main: main.o gate.o and.o or.o value.o
	g++ main.o gate.o and.o or.o value.o -o main

main.o: main.cpp
	g++ -c main.cpp

gate.o: gate.cpp
	g++ -c gate.cpp

value.o: value.cpp
	g++ -c value.cpp


and.o: and.cpp
	g++ -c and.cpp

or.o: or.cpp
	g++ -c or.cpp

clean:
	del *.o main.exe