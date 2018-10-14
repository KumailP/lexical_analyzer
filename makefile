all: new

scanner: 
	g++ -Wall -g -o scanner lexicalAnalyzer.cpp

new: clean scanner run

run: scanner
	./scanner

clean:
	rm scanner.exe