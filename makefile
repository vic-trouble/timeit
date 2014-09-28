default:
	g++ -std=gnu++11 -Wall -Werror -pedantic-errors ./tests/tests.cpp -I. -o ./tests/tests
	
clear:
	rm ./tests/tests
	
test:
	./tests/tests