CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lBearLibTerminal

TARGET = TerminalTrainers

SOURCES = main.cpp Tile.cpp TileMap.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
