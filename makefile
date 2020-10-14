CXX = g++
CXXFLAGS = -Wall -g

driver: Passenger.o Train.o Route.o driver.cpp
	$(CXX) $(CXXFLAGS) Passenger.o Train.o Route.o driver.cpp -o driver

Route.o: Route.h Route.cpp Stop.cpp
	$(CXX) $(CXXFLAGS) -c Route.cpp

Train.o: Train.h Train.cpp Route.o Passenger.o
	$(CXX) $(CXXFLAGS) -c Train.cpp

Passenger.o: Passenger.h Passenger.cpp 
	$(CXX) $(CXXFLAGS) -c Passenger.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./driver

val:
	valgrind ./driver

gdb:
	gdb driver
