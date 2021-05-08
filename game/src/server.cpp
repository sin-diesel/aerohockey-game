#include "server.h"
#include "puck.h"
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
    adresses.push_back(client_addr); //save client's adress
    ports.push_back(client_port);    //save client's port

    std::cout << "Packet from client received " << std::endl;
    std::cout << "Client addr: " << client_addr << std::endl;
    std::cout << "Client port: " << client_port << std::endl;
}

void Server::get_updates() //receives data about strikers moving from clients
{
    sf::Packet packet;
    sf::Vector2f pos;
    client_sockets[0].receive(packet, adresses[0], ports[0]);
    packet >> pos.x >> pos.y;
    striker1.calculate_speed(pos);
    client_sockets[1].receive(packet, adresses[1], ports[1]);
    packet >> pos.x >> pos.y;
    striker2.calculate_speed(pos);
}

 void Server::send_updates() //calculates new cooridinates of puck and strikers and sends to clients
{
    sf::Packet packet;
    sf::Vector2f pos, pos_striker1, pos_striker2;
    pos_striker1 = striker1.get_coord();
    packet << pos_striker1.x << pos_striker2.y;
    pos_striker2 = striker2.get_coord();
    packet << pos_striker2.x << pos_striker2.y;
    pos = puck.update(pos_striker1, pos_striker2);
    packet << pos.x << pos.y;
    client_sockets[0].send(packet, adresses[0], ports[0]);
    client_sockets[1].send(packet, adresses[1], ports[1]);
}

void Server::run() {
    while (1) {
        handle_connections();
    }
}