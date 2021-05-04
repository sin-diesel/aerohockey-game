
CXX = g++
CXXFLAGS = -std=c++11 -g -I $(INCLUDE)
SRC_PATH = game/src
OBJ_PATH = game/obj
INCLUDE = game/include
DLIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/game.o: $(SRC_PATH)/game.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/game.o

all: $(OBJ_PATH)/main.o $(OBJ_PATH)/game.o
	g++ $^ -o game.out $(DLIB)

clean:
	-rm game.out
	rm $(OBJ_PATH)/*.o
