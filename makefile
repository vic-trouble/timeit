default:
	g++ -std=c++0x -Wall -Werror -pedantic-errors ./tests/tests.cpp -I. -o ./tests/tests
	
clear:
	rm ./tests/tests
	
test:
	./tests/tests