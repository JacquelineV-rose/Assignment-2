CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic


all: proj2.x test_list.x

proj2.x: MyMemory.o mem_manager.o
	$(CXX) $(CXXFLAGS) -o proj2.x MyMemory.o mem_manager.o

test_list.x: test_list.o
	$(CXX) $(CXXFLAGS) -o test_list.x test_list.o

MyMemory.o: MyMemory.cpp MyMemory.h List.h List.hpp
	$(CXX) $(CXXFLAGS) -c MyMemory.cpp

mem_manager.o: mem_manager.cpp MyMemory.h
	$(CXX) $(CXXFLAGS) -c mem_manager.cpp


test_list.o: test_list.cpp List.h List.hpp
	$(CXX) $(CXXFLAGS) -c test_list.cpp

clean: 
	rm -f *.o *.x core.*

