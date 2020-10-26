
CXX = g++
CXXFLAGS = -Wall -Wpedantic -g -Wextra

# ****************************************************
# Targets needed to bring the executable up to date

cachesim: cache_simulator.o cache.o set.o
	$(CXX) $(CXXFLAGS) -o cachesim cache_simulator.o cache.o set.o

# The main.o target can be written more simply

cache_simulator.o: cache_simulator.cpp 
	$(CXX) $(CXXFLAGS) -c cache_simulator.cpp
cache.o: cache.cpp cache.h 
	$(CXX) $(CXXFLAGS) -c cache.cpp cache.h
set.o: set.cpp set.h block.h
	$(CXX) $(CXXFLAGS) -c set.cpp set.h block.h 
clean:
	rm cachesim cache_simulator.o block.h.* set.h.* cache.o cache.h.* set.o