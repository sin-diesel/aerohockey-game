#pragma once
#include "library.h"
#include "dynamic.h"

class Server {
private:
    
    int number_of_clients = 0;
    ServerDynamicObject puck;
    ServerDynamicObject striker1, striker2;
    sf::Vector2i score;
    std::vector <bool> keyboard_control = {false, false};
    unsigned short port = 0;
    sf::UdpSocket socket;
    sf::IpAddress addr;
    sf::Packet connection_info;
    std::vector<sf::UdpSocket*> client_sockets;
    std::vector<sf::IpAddress> adresses;
    std::vector<short unsigned> ports;
    sf::SocketSelector client_selector;
    sf::SocketSelector server_selector;

public:
    Server();
    ~Server();
    void run();
    sf::Vector2i update_score(int side);
    void handle_connections(int client_number);
    void init_sockets();
    std::vector<bool> get_updates(std::vector<sf::Packet>& data);
    bool send_updates(sf::Packet& data, int i);
    void keyboard_update_strikers_position();
    void keyboard_update_strikers(std::vector<int>& key, int i);
    void update_and_send(int i);
    void mouse_update_strikers(sf::Vector2f pos, int i);
    void time_out();
};


sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& pos);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& pos);

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2i& pos);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2i& pos);
