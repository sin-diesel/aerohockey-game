#include "server.h"
#include <iostream>

Server::Server() {
    port = PORT;
    if (socket.bind(PORT) != sf::UdpSocket::Done) {
        std::cerr << "Error binding server socket. " << std::endl;
    }
    addr = sf::IpAddress::LocalHost;
}

Server::~Server() {
    socket.unbind();
}

void Server::handle_connections() {

    sf::Packet connection_info;
    sf::IpAddress client_addr;
    unsigned short client_port;
    
    std::cout << "Waiting for incoming connection from client..." << std::endl; 

    socket.receive(connection_info, client_addr, client_port);

    std::cout << "Packet from client received " << std::endl;
    std::cout << "Client addr: " << client_addr << std::endl;
    std::cout << "Client port: " << client_port << std::endl;
}

void Server::get_updates() {

}

void Server::run() {
    while (1) {
        handle_connections();
    }
}