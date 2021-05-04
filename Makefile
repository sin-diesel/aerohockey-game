
CXX = g++
CXXFLAGS = -std=c++11 -g
SRC_PATH = game/src
OBJ_PATH = game/obj
DLIB = -lsfml-graphics -lsfml-window -lsfml-system

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/main.o

all: $(OBJ_PATH)/main.o
	g++ $^ -o game.out $(DLIB)

clean:
	-rm game.out
	rm $(OBJ_PATH)/*.o
