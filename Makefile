CXX = g++
CXXFLAGS = -std=c++20 
LDFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs

TARGET = TerminalTrainers

SOURCES = main.cpp Pokemon.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
