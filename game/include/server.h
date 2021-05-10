#pragma once
#include "game.h"
#include "puck.h"
#include <vector>

#define PORT 54000
#define CLIENT_1_PORT 54001
#define CLIENT_2_PORT 54002

class Server {
private:
    int number_of_clients = 0;
    // time interval used to exchange data packets between server and client
    Puck puck;
    Striker striker1, striker2;

    unsigned short port = 0;
    sf::UdpSocket socket;
    sf::IpAddress addr;
    
    sf::Packet connection_info;
    // sockets for each client
    std::vector<sf::UdpSocket*> client_sockets;
    std::vector<sf::IpAddress> adresses;
    std::vector<short unsigned> ports;
    //std::vector<short unsigned> available_ports;
public:
    Server();
    ~Server();
    void run(Game& game);
    // accept incoming connections in blocking mode
    void handle_connections(int client_number);
    void init_sockets();
    // get updates from all clients
    bool get_updates(std::vector<sf::Packet>& data);
    // send updated info for rendering to all clients
    bool send_updates(std::vector<sf::Packet>& data);
    // calculate all information that is going to be sent back to client
    void calculate_changes();
};