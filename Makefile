all:
	g++ -o drake src/*.cpp

debug:
	g++ -g -Wall -pedantic -o drake src/*.cpp

clean:
	rm drake
