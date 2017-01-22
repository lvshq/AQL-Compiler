Main: Tokenizer.o Parser.o Lexer.o main.cpp regex.cpp
	g++ -std=c++0x -o Aql main.cpp Tokenizer.o Parser.o Lexer.o

Tokenizer.o: Tokenizer.cpp Tokenizer.h
	g++ -std=c++0x -c Tokenizer.cpp

Lexer.o: Lexer.cpp Lexer.h
	g++ -std=c++0x -c Lexer.cpp

Parser.o: Parser.cpp Parser.h
	g++ -std=c++0x -c Parser.cpp

clean:
	rm *.o
