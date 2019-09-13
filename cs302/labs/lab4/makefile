CXX = g++
CXXFLAGS = -std=c++11

all: create_file

create_file: create_file.o file_txt.o file_bin.o file_mem.o
	$(CXX) $(CXXFLAGS) -o $@ create_file.o file_txt.o file_bin.o file_mem.o
	
create_file.o: create_file.cpp file.hpp pfile.hpp
	$(CXX) $(CXXFLAGS) -c create_file.cpp	

file_txt.o: file_txt.cpp file.hpp pfile.hpp
	$(CXX) $(CXXFLAGS) -c file_txt.cpp

file_bin.o: file_bin.cpp file.hpp pfile.hpp
	$(CXX) $(CXXFLAGS) -c file_bin.cpp

file_mem.o: file_mem.cpp file.hpp pfile.hpp
	$(CXX) $(CXXFLAGS) -c file_mem.cpp

clean:
	rm -f create_file.o file_txt.o file_bin.o file_mem.o

