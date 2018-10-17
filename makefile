all: new

scanner: 
	g++ -std=c++11 -Wall -g -o scanner lexicalAnalyzer.cpp

new: clean scanner run

run: scanner
	./scanner

clean:
	rm -f scanner.exe
