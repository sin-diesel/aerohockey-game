#pragma once
#include "library.h"
#include "dynamic.h"

#define CLIENT_1_PORT 54001
#define CLIENT_2_PORT 54002

class Server {
private:
    int number_of_clients = 0;

    ServerDynamicObject puck;
    ServerDynamicObject striker1, striker2;
    sf::Vector2i score;

    unsigned short port = 0;
    sf::UdpSocket socket;
    sf::IpAddress addr;
    
    sf::Packet connection_info;
    // sockets for each client
    std::vector<sf::UdpSocket*> client_sockets;
    std::vector<sf::IpAddress> adresses;
    std::vector<short unsigned> ports;

    sf::SocketSelector client_selector;
    sf::SocketSelector server_selector;
    //std::vector<short unsigned> available_ports;
public:
    Server();
    ~Server();
    void run();
    sf::Vector2i update_score(int side);
    // accept incoming connections in blocking mode
    void handle_connections(int client_number);
    void init_sockets();
    // get updates from all clients
    std::vector<bool> get_updates(std::vector<sf::Packet>& data);
    // send updated info for rendering to all clients
    bool send_updates(sf::Packet& data, int i);
    // calculate all information that is going to be sent back to client
    void calculate_changes();
    void update_strikers(sf::Vector2f, sf::Vector2f);
    
};


sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& pos);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& pos);

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2i& pos);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2i& pos);
