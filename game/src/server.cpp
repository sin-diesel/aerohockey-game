#include "server.h"
#include "puck.h"
#include <iostream>

Server::Server() {
    port = PORT;
    if (socket.bind(PORT) != sf::UdpSocket::Done) {
        std::cerr << "Error binding server socket. " << std::endl;
    }
    socket.setBlocking(true);

    // create sockets for clients
    for (int i = 0; i < 2; ++i) { 
        //client_sockets.push_back(*client_socket);
        sf::UdpSocket* client_socket = new sf::UdpSocket();
        client_sockets.push_back(client_socket);

        if (client_sockets[i]->bind(sf::Socket::AnyPort) != sf::UdpSocket::Done) {
            std::cerr << "Error binding client socket on server. " << std::endl;
        }

        client_sockets[i]->setBlocking(true);
        client_selector.add(*(client_sockets[i]));

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

bool Server::get_updates(std::vector<sf::Packet>& data) //receives data about strikers moving from clients
{
    sf::IpAddress client_address;
    unsigned short client_port;

    // here we receive not from the main server socket, but instead from client socket
    //client_selector.wait()
    if (client_selector.wait(sf::microseconds(100))) {
        for (int i = 0; i < 2; ++i) {
            if (client_selector.isReady(*(client_sockets[i]))) {
                client_sockets[i]->receive(data[i], client_address, client_port);
                std::cout << "Received from: " << std::endl;
                std::cout << client_address << std::endl << client_port << std::endl;
            } else {
                std::cerr << "Error receiving packet from client. " << std::endl;
                std::cerr << std::endl;
            }
        }
    }
        // if (client_sockets[i]->receive(data[i], client_address, client_port) != sf::Socket::Done) {
        //     std::cerr << "Error receiving packet from client. " << std::endl;
        //     std::cerr << std::endl;
        //     return false;
        // }

        // std::cout << "Received from: " << std::endl;
        // std::cout << client_address << std::endl << client_port << std::endl;

    return true;
}

bool Server::send_updates(std::vector<sf::Packet>& data) // calculates new cooridinates of puck and strikers and sends to clients
{
    for (int i = 0; i < 2; ++i) {
        if (client_sockets[i]->send(data[i], adresses[i], ports[i]) != sf::Socket::Done) {
            std::cerr << "Error sending data to client. " << std::endl;
            std::cerr << std::endl;
            return false;
        }
    }

    return true;
}

void Server::run(Game& game) {
    // handle 2 clients
    sf::Clock clock;
    sf::Time elapsed;

    std::vector<sf::Packet> data;
    for (int i = 0; i < 2; ++i) {
        data.push_back(sf::Packet());
    }
    
    std::vector<sf::Packet> response;
    for (int i = 0; i < 2; ++i) {
        response.push_back(sf::Packet());
    }

    sf::Vector2f client_direction;

    while (1) {
        bool received = true;
        elapsed = clock.getElapsedTime();
        if (elapsed > game.get_update_time()) {

            received = get_updates(data);

            std::cout << "Packet from client received: " << std::endl;

            if (received) {
                for (int i = 0; i < 2; ++i) {
                    data[i] >> client_direction.x >> client_direction.y;
                    std::cout << "Client  " << i << " direction: " << client_direction.x << " " 
                                                << client_direction.y << std::endl;
                    client_direction.x += 1.0f;
                    client_direction.y += 1.0f;

                    data[i].clear();
                    response[i].clear();
                    
                    // data[i] << client_direction.x << client_direction.y;
                    response[i] << client_direction.x << client_direction.y;
                    std::cout << "Client  " << i << " direction updated: " << client_direction.x << " " \
                                                << client_direction.y << std::endl;
                }
                send_updates(response);
            }

            clock.restart();
        }
    }
}