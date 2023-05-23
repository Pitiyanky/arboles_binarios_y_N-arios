CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

main: main.cpp arbolB.hpp ArbolN.hpp NodoArbol.hpp NodoBinario.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o arboles

clean:
	rm -f arboles