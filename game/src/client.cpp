#include "../include/client.h"

Client::Client() {
    addr = sf::IpAddress::Any;
    port = sf::Socket::AnyPort;
    number = 0;
    if (socket.bind(port) != sf::Socket::Done) {
        std::cerr << "Error binding client socket." << std::endl;
    }
    socket.setBlocking(true);
    std::cout << "Initializing client." << std::endl;

    // connect to local machine
    server_addr = sf::IpAddress((sf::IpAddress::LocalHost));
    std::cout << "Address of server is: " << server_addr << std::endl;
    
    // connect to server
    connect(server_addr);
    server_port = get_port();
    std::cout << "Port received from server: " << server_port << std::endl;

    sf::Clock clock;
    sf::Time elapsed;
    std::cout << "client number is " << number << std::endl;
}

Client::~Client() {
    socket.unbind();
}

bool Client::send_updates(sf::Packet& packet) {
    if (socket.send(packet, server_addr, server_port) != sf::Socket::Done) {
        return false;
    }
    return true;
}

bool Client::receive_updates(sf::Packet& packet, sf::IpAddress& server_addr, unsigned short& port) {
    if (socket.receive(packet, server_addr, port) != sf::Socket::Done) {
        return false;
    }
    return true;
}

void Client::connect(sf::IpAddress server_addr) {
    sf::Packet connection_info;
    if (socket.send(connection_info, server_addr, PORT) != sf::Socket::Done) {
        std::cerr << "Error establishing connection to server." << std::endl;
    }
    std::cout << server_addr << std::endl;
}

unsigned short Client::get_port() {
    sf::Packet packet;
    sf::IpAddress server_addr;
    unsigned short port;

    socket.setBlocking(true);

    if (socket.receive(packet, server_addr, port) != sf::Socket::Done) {
        std::cerr << "Error receiving port from server. " << std::endl;
        //socket.setBlocking(false);
        return 0;
    } else {
        packet >> port >> number;
        //socket.setBlocking(false);
        return port;
    }
}


sf::Packet Client::process_input() {

    // test version for processing input
    // NetworkPacket data;

    float pos1_x = 1.0f;
    float pos1_y = 1.0f;
    // data.pos2_x = 2.0f;
    // data.pos2_y = 2.0f;
    // data.puck_x = 3.0f;
    // data.puck_y = 3.0f;

    sf::Packet packet;
    packet << pos1_x << pos1_y;

    return packet;
}

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& pos)
{
    return packet << pos.x << pos.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& pos)
{
    return packet >> pos.x >> pos.y;
}

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2i& pos)
{
    return packet << pos.x << pos.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2i& pos)
{
    return packet >> pos.x >> pos.y;
}
