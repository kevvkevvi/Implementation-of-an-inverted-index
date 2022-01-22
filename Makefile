CXX = g++
CXXFLAGS = -Wall -std=c++11

inverter: inverter.cc
	$(CXX) $(CXXFLAGS) -o $@ inverter.cc

clean:
	rm -f inverter

