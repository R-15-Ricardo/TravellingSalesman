all: TS

TS: main.o graphLib.o rColors.o
	g++ main.o graphLib.o rColors.o -o TS -lsfml-graphics -lsfml-system -lsfml-window

main.o: main.cpp
	g++ -c main.cpp

graphLib.o: graphLib.cpp
	g++ -c graphLib.cpp

rColors.o: rColors.cpp
	g++ -c rColors.cpp

clean:
	rm main.o graphLib.o rColors.o TS
