all: scanner

scanner: 
	g++ -Wall -g -o scanner lexicalAnalyzer.cpp
     
clean:
	rm scanner.exe