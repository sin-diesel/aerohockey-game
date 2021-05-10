#include "server.h"
#include "puck.h"
#include <iostream>

Server::Server() {
    port = PORT;
    if (socket.bind(PORT) != sf::UdpSocket::Done) {
        std::cerr << "Error binding server socket. " << std::endl;
    }
    socket.setBlocking(true);

    // available_ports[0] = CLIENT_1_PORT;
    // available_ports[1] = CLIENT_2_PORT;

    // create sockets for clients
    for (int i = 0; i < 2; ++i) { 
        //client_sockets.push_back(*client_socket);
        sf::UdpSocket* client_socket = new sf::UdpSocket();
        client_sockets.push_back(client_socket);

        if (client_sockets[i]->bind(sf::Socket::AnyPort) != sf::UdpSocket::Done) {
            std::cerr << "Error binding client socket on server. " << std::endl;
        }

        client_sockets[i]->setBlocking(false);

    }

    addr = sf::IpAddress::LocalHost;
}

Server::~Server() {
    socket.unbind();
    for (int i = 0; i < client_sockets.size(); ++i) {
        client_sockets[i]->unbind();
    }

    for (int i = 0; i < 2; ++i) {
        delete client_sockets[i];
    }
}

void Server::handle_connections(int client_number) {

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

    unsigned short new_port = client_sockets[client_number]->getLocalPort();
    std::cout << "Port distrubuted for new client: " << new_port << std::endl;
    
    sf::Packet response;
    response << new_port;
    socket.send(response, client_addr, client_port);
}

void Server::get_updates(sf::Packet& packet) //receives data about strikers moving from clients
{
    sf::IpAddress client_address;
    unsigned short client_port;

    // here we receive not from the main server socket, but instead from client socket
    for (int i = 0; i < 2; ++i) {
        if (client_sockets[i]->receive(packet, client_address, client_port) != sf::Socket::Done) {
            std::cerr << "Error receiving packet from client. " << std::endl;
            std::cerr << std::endl;
        }

        std::cout << "Received from: " << std::endl;
        std::cout << client_address << std::endl << client_port << std::endl;
    }

    // packet >> pos.x >> pos.y;
    // std::cout << "Received from: " << std::endl;
    // std::cout << client_address << std::endl << client_port << std::endl;
    // std::cout << "Packet from client received: " << std::endl;
    // std::cout << "pos.x: " << pos.x << std::endl;
    // std::cout << "pos.y: " << pos.y << std::endl;
    //striker1.calculate_speed(pos);
    //client_sockets[1].receive(packet, adresses[1], ports[1]);
    //packet >> pos.x >> pos.y;
    //striker2.calculate_speed(pos);
}

 void Server::send_updates(sf::Packet& packet) // calculates new cooridinates of puck and strikers and sends to clients
{
    for (int i = 0; i < 2; ++i) {
        if (client_sockets[i]->send(packet, adresses[i], ports[i]) != sf::Socket::Done) {
            std::cerr << "Error sending data to client. " << std::endl;
            std::cerr << std::endl;
        }
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

            sf::Packet data;
            sf::Vector2f pos;

            get_updates(data);
            data >> pos.x >> pos.y;
            // update
            std::cout << "Packet from client received: " << std::endl;
            std::cout << "pos.x: " << pos.x << std::endl;
            std::cout << "pos.y: " << pos.y << std::endl;

            pos.x += 1.0f;
            pos.y += 1.0f;

            data << pos.x << pos.y;

            send_updates(data);
            
            std::cout << "Packet to client sent: " << std::endl;
            std::cout << "pos.x: " << pos.x << std::endl;
            std::cout << "pos.y: " << pos.y << std::endl;
            clock.restart();
        }
    }
}