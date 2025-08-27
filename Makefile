CXXFLAGS=--std=c++11


bvh_parser.o: bvh_parser.cpp bvh_parser.h
	$(CXX) $(CXXFLAGS) -c bvh_parser.cpp

json.o:
	pass

base: json.o bvh_parser.o
	$(CXX) $(CXXFLAGS) -o base json.o bvh_parser.o

bonus: bvh_parser.o json.cpp bvh_parser.h
	rm json.o
	rm bvh_parser.o
	$(CXX) $(CXXFLAGS) -c json.cpp
	$(CXX) $(CXXFLAGS) -o bonus json.o bvh_parser.o

clean:
	rm -rf *.o base bonus
