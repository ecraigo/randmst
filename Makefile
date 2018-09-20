CXX := g++
CXXFLAGS := -std=c++11

randmst: randmst.cpp
	$(CXX) $(CXXFLAGS) randmst.cpp -o randmst
clean:
	rm randmst
