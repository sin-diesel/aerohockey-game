#include "../include/client.h"

Client::Client(sf::IpAddress& address, bool keyboard_cont):
    keyboard_control(keyboard_cont) {
    addr = sf::IpAddress::Any;
    port = sf::Socket::AnyPort;
    number = 0;
    if (socket.bind(port) != sf::Socket::Done) {
        std::cerr << "Error binding client socket." << std::endl;
    }
    socket.setBlocking(true);
    std::cout << "Initializing client." << std::endl;

    // connect to local machine
    server_addr = address;
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
    connection_info << keyboard_control;
    if (socket.send(connection_info, server_addr, PORT) != sf::Socket::Done) {
        std::cerr << "Error establishing connection to server." << std::endl;
    }
}

unsigned short Client::get_port() {
    sf::Packet packet;
    sf::IpAddress server_addr;
    unsigned short port;
    int num;
    socket.setBlocking(true);

    if (socket.receive(packet, server_addr, port) != sf::Socket::Done) {
        std::cerr << "Error receiving port from server. " << std::endl;
        //socket.setBlocking(false);
        return 0;
    } else {
        packet >> port >> num;
        set_number(num);
        //socket.setBlocking(false);
        return port;
    }
}

int Client::get_number() {
    return number;
}

void Client::set_number(int num) {
    number = num;
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
