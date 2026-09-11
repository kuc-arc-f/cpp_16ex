CXX = g++
#CXX = clang++

#CXXFLAGS = -shared -fPIC -std=c++17 -lsqlite3 -lcurl -luuid
CXXFLAGS = -shared -fPIC -std=c++17

TARGET = libsample.so
all: $(TARGET)

$(TARGET): sample.o
	$(CXX) $(CXXFLAGS) sample.o -o $(TARGET)

sample.o: sample.cpp
	$(CXX) $(CXXFLAGS) -c sample.cpp

clean:
	rm *.o $(TARGET)
