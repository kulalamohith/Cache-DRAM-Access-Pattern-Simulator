CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

OBJS = main.o SimpleCache.o SimpleDRAM.o

simulator: $(OBJS)
	$(CXX) $(CXXFLAGS) -o simulator $(OBJS)

main.o: main.cpp SimpleCache.h SimpleDRAM.h
	$(CXX) $(CXXFLAGS) -c main.cpp

SimpleCache.o: SimpleCache.cpp SimpleCache.h
	$(CXX) $(CXXFLAGS) -c SimpleCache.cpp

SimpleDRAM.o: SimpleDRAM.cpp SimpleDRAM.h
	$(CXX) $(CXXFLAGS) -c SimpleDRAM.cpp

clean:
	rm -f *.o simulator
