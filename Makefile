
CXX = g++
CXXFLAGS = -std=c++11 -g -I $(INCLUDE)
SRC_PATH = game/src
OBJ_PATH = game/obj
INCLUDE = game/include
OBJ = $(OBJ_PATH)/main.o $(OBJ_PATH)/game.o $(OBJ_PATH)/puck.o $(OBJ_PATH)/server.o
SRC = $(SRC_PATH)/main.cpp $(SRC_PATH)/game.cpp $(SRC_PATH)/puck.cpp $(SRC_PATH)/server.cpp
DLIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/game.o: $(SRC_PATH)/game.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/game.o

$(OBJ_PATH)/server.o: $(SRC_PATH)/server.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/server.o

$(OBJ_PATH)/puck.o: $(SRC_PATH)/puck.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/puck.o

all: $(OBJ)
	g++ $^ -o game.out $(DLIB)

clean:
	-rm game.out
	rm $(OBJ_PATH)/*.o
