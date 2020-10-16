
CXX = g++
CXXFLAGS = -Wall -Wpedantic -g -Wextra

# ****************************************************
# Targets needed to bring the executable up to date

cachesim: cache_simulator.o cache.o
	$(CXX) $(CXXFLAGS) -o cachesim cache_simulator.o cache.o

# The main.o target can be written more simply

cache_simulator.o: cache_simulator.cpp 
	$(CXX) $(CXXFLAGS) -c cache_simulator.cpp
cache.o: cache.cpp cache.h set.h block.h
	$(CXX) $(CXXFLAGS) -c cache.cpp set.h block.h cache.h
clean:
	rm cachesim cache_simulator.o block.h.* set.h.* cache.o cache.h.*