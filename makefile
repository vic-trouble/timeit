CXXPARAMS = -std=c++0x -Wall -Werror -pedantic-errors -I.

default:
	$(CXX) $(CXXPARAMS) ./tests/tests.cpp -o ./tests/tests.exe
	$(CXX) $(CXXPARAMS) ./examples/sleep.cpp -o ./examples/sleep.exe
	
clear:
	rm ./tests/tests.exe
	rm ./examples/sleep.exe
	
test:
	./tests/tests
	