#make bash file executable
#compile c++ code
CXX = g++
CXXFLAGS= -Wformat -O3

TR_trl:
	chmod +x TRate_trl.sh

	$(CXX) -o $@ $(CXXFLAGS) TR_trl.cpp
	
clean:
