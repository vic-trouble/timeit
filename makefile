default:
	g++ -std=c++11 ./tests/tests.cpp -I. -o ./tests/tests
	
clear:
	rm ./tests/tests
	
test:
	./tests/tests