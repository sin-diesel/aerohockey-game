
CXX = g++
CXXFLAGS = -std=c++11 -g -I $(INCLUDE)
SRC_PATH = game/src
OBJ_PATH = game/obj
INCLUDE = game/include

define OBJ

$(OBJ_PATH)/main.o $(OBJ_PATH)/game.o $(OBJ_PATH)/dynamic.o $(OBJ_PATH)/scoreboard.o $(OBJ_PATH)/server.o
endef

define SERVER_OBJ
$(OBJ_PATH)/game.o $(OBJ_PATH)/dynamic.o $(OBJ_PATH)/scoreboard.o $(OBJ_PATH)/server.o $(OBJ_PATH)/main_server.o
endef

define CLIENT_OBJ
$(OBJ_PATH)/game.o $(OBJ_PATH)/dynamic.o $(OBJ_PATH)/scoreboard.o $(OBJ_PATH)/client.o $(OBJ_PATH)/main_client.o
endef

define SRC
$(SRC_PATH)/main.cpp $(SRC_PATH)/game.cpp $(SRC_PATH)/dynamic.cpp $(SRC_PATH)/scoreboard.cpp

	$(SRC_PATH)/server.cpp $(SRC_PATH)/main_server.cpp $(SRC_PATH)/main_client.cpp
endef

$(OBJ_PATH)/main.o: $(SRC_PATH)/main.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/main.o

$(OBJ_PATH)/game.o: $(SRC_PATH)/game.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/game.o

$(OBJ_PATH)/server.o: $(SRC_PATH)/server.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/server.o

$(OBJ_PATH)/dynamic.o: $(SRC_PATH)/dynamic.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/dynamic.o

$(OBJ_PATH)/scoreboard.o: $(SRC_PATH)/scoreboard.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/scoreboard.o

$(OBJ_PATH)/client.o: $(SRC_PATH)/client.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/client.o

$(OBJ_PATH)/main_server.o: $(SRC_PATH)/main_server.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/main_server.o

$(OBJ_PATH)/main_client.o: $(SRC_PATH)/main_client.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $(OBJ_PATH)/main_client.o

# OS-dependency variables
OS=$(shell uname)
export OS
ifeq ($(OS), Darwin)
# set variables for Darwin
DLIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
else
DLIB = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lstdc++fs
endif

all: $(OBJ)
	g++ $^ -o game.out $(DLIB)
	
server: $(SERVER_OBJ)
	g++ $^ -o server.out $(DLIB)

client: $(CLIENT_OBJ)
	g++ $^ -o client.out $(DLIB)

clean:
	-rm *.out
	-rm $(OBJ_PATH)/*.o