CXXPARAMS = -std=c++0x -Wall -Werror -pedantic-errors -I.

default:
	
clean:
	rm -f ./tests/*.exe
	rm -f ./examples/*.exe
	
test:
	$(CXX) $(CXXPARAMS) ./tests/tests.cpp -o ./tests/tests.exe
	./tests/tests.exe

examples:
	$(CXX) $(CXXPARAMS) ./examples/sleep.cpp -o ./examples/sleep.exe
	$(CXX) $(CXXPARAMS) ./examples/precise.cpp -o ./examples/precise.exe
	$(CXX) $(CXXPARAMS) ./examples/vector-vs-list.cpp -o ./examples/vector-vs-list.exe
