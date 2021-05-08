#pragma once
#include "game.h"
#include "puck.h"
#include <vector>

#define PORT 54000

class Server {
private:
    int number_of_clients = 0;
    Puck puck;
    Striker striker1, striker2;

    unsigned short port = 0;
    sf::UdpSocket socket;
    sf::IpAddress addr;
    
    sf::Packet connection_info;
    // sockets for each client
    std::vector<sf::UdpSocket> client_sockets;
    std::vector<sf::IpAddress> adresses;
    std::vector<short unsigned> ports;
public:
    Server();
    ~Server();
    void run();
    // accept incoming connections in blocking mode
    void handle_connections();
    // get updates from all clients
    void get_updates();
    // send updated info for rendering to all clients
    void send_updates();
    // calculate all information that is going to be sent back to client
    void calculate_changes();
};