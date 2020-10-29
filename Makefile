
CXX = g++
CXXFLAGS = -Wall -Wpedantic -g -Wextra

# ****************************************************
# Targets needed to bring the executable up to date

csim: cache_simulator.o cache.o set.o
	$(CXX) $(CXXFLAGS) -o csim cache_simulator.o cache.o set.o

# The main.o target can be written more simply

cache_simulator.o: cache_simulator.cpp cache.o set.o
	$(CXX) $(CXXFLAGS) -c cache_simulator.cpp
cache.o: cache.cpp cache.h set.o
	$(CXX) $(CXXFLAGS) -c cache.cpp cache.h
set.o: set.cpp set.h block.h
	$(CXX) $(CXXFLAGS) -c set.cpp set.h block.h 

.PHONY: solution.zip
solution.zip:
	rm -f solution.zip
	zip -9r $@ Makefile *.h *.cpp README

clean:
	rm csim cache_simulator.o block.h.* set.h.* cache.o cache.h.* set.o