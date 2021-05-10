#include "server.h"
#include "puck.h"
#include <iostream>

Server::Server() {
    port = PORT;
    if (socket.bind(PORT) != sf::UdpSocket::Done) {
        std::cerr << "Error binding server socket. " << std::endl;
    }
    socket.setBlocking(false);
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

    // Block until client is connected
    socket.setBlocking(true);
    socket.receive(connection_info, client_addr, client_port);
    socket.setBlocking(false);
    
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

    sf::IpAddress client_address;
    unsigned short client_port;

    if (socket.receive(packet, client_address, client_port) != sf::Socket::Done) {
        std::cerr << "Error receiving packet from client. " << std::endl;
        std::cerr << std::endl;
        return;
    }

    packet >> pos.x >> pos.y;
    std::cout << "Received from: " << std::endl;
    std::cout << client_address << std::endl << client_port << std::endl;
    std::cout << "Packet from client received: " << std::endl;
    std::cout << "pos.x: " << pos.x << std::endl;
    std::cout << "pos.y: " << pos.y << std::endl;
    //striker1.calculate_speed(pos);
    //client_sockets[1].receive(packet, adresses[1], ports[1]);
    //packet >> pos.x >> pos.y;
    //striker2.calculate_speed(pos);
}

 void Server::send_updates() //calculates new cooridinates of puck and strikers and sends to clients
{
    sf::Packet packet;
    sf::Vector2f pos, pos_striker1, pos_striker2;
    pos_striker1 = striker1.get_coord();
    packet << pos_striker1.x << pos_striker2.y;
    // pos_striker2 = striker2.get_coord();
    // packet << pos_striker2.x << pos_striker2.y;
    // pos = puck.update(pos_striker1, pos_striker2);
    // packet << pos.x << pos.y;
    if (socket.send(packet, adresses[0], ports[0]) != sf::Socket::Done) {
        std::cerr << "Error sending data to client. " << std::endl;
        std::cerr << std::endl;
    }
    //client_sockets[1].send(packet, adresses[1], ports[1]);
}

void Server::run(Game& game) {
    // handle 1 clients
    sf::Clock clock;
    sf::Time elapsed;
    while (1) {
        elapsed = clock.getElapsedTime();
        if (elapsed > game.get_update_time()) {
            get_updates();
            send_updates();
            clock.restart();
        }
    }
}