#include "server.h"
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
    //ServerDynamicObject puck, striker1, striker2;
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
    response << new_port << client_number;
    socket.send(response, client_addr, client_port);
}

bool Server::get_updates(std::vector<sf::Packet>& data) //receives data about strikers moving from clients
{
    sf::IpAddress client_address;
    unsigned short client_port;

    // here we receive not from the main server socket, but instead from client socket
    //client_selector.wait()
    if (client_selector.wait(sf::milliseconds(100))) {
        for (int i = 0; i < 2; ++i) {
            if (client_selector.isReady(*(client_sockets[i]))) {
                client_sockets[i]->receive(data[i], client_address, client_port);
                std::cout << "Received from: " << std::endl;
                std::cout << client_address << std::endl << client_port << std::endl;
            } else {
                //!!!!! std::cerr << "Error receiving packet from client. " << std::endl;
                std::cerr << std::endl;
            }
        }
    } else {
        return false;
    }
        // if (client_sockets[i]->receive(data[i], client_address, client_port) != sf::Socket::Done) {
        //     std::cerr << "Error receiving packet from client. " << std::endl;
        //     std::cerr << std::endl;
        //     return false;
        // }

        // std::cout << "Received from: " << std::endl;
        // std::cout << client_address << std::endl << client_port << std::endl;

    return true;
//>>>>>>> client-server-comm
}
//<<<<<<< HEAD
//     sf::Packet packet;
//     sf::Vector2f pos1, pos2;
//     client_sockets[0].receive(packet, adresses[0], ports[0]);
//     client_sockets[1].receive(packet, adresses[1], ports[1]);
//     packet >> pos1.x >> pos1.y >> pos2.x >> pos2.y;
//     update_strikers(pos1, pos2);
// }

void Server::update_strikers(sf::Vector2f pos1, sf::Vector2f pos2)
{
    if ((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y) <= RADIUS * RADIUS) {
        pos1 = striker1.get_coord(), pos2 = striker2.get_coord();
        //std::cout << "ASSERT" << std::endl;
    }
    striker1.calculate_speed(pos1);
    striker2.calculate_speed(pos2);
    striker1.set_coord(pos1);
    striker2.set_coord(pos2);
}
//=======

bool Server::send_updates(std::vector<sf::Packet>& data) // calculates new cooridinates of puck and strikers and sends to clients
{
// <<<<<<< HEAD
//     sf::Packet packet;
//     sf::Vector2f pos;
//     packet << pos.x << pos.y;
//     striker1.calculate_speed(pos);
//     packet << pos.x << pos.y;
//     striker2.calculate_speed(pos);
//     pos = puck.update(striker1, striker2);
//     packet << pos.x << pos.y;
//     client_sockets[0].send(packet, adresses[0], ports[0]);
//     client_sockets[1].send(packet, adresses[1], ports[1]);
//=======
    for (int i = 0; i < 2; ++i) {
        if (client_sockets[i]->send(data[i], adresses[i], ports[i]) != sf::Socket::Done) {
            std::cerr << "Error sending data to client. " << std::endl;
            std::cerr << std::endl;
            return false;
        }
    }

    return true;
//>>>>>>> client-server-comm
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

    sf::Vector2f pos1[2];

    while (1) {
        bool received = true;
        elapsed = clock.getElapsedTime();
        if (elapsed > sf::milliseconds(10)) {

            received = get_updates(data);

            //std::cout << "Packet from client received: " << std::endl;

            //if (received) {
                for (int i = 0; i < 2; ++i) {
                    if (received) {
                        data[i] >> pos1[i];

                        std::cout << "Client  " << i << " pos: " << pos1[i].x << " " << pos1[i].y << " " << std::endl;
                    }
                    //std::cout << "B striker position " << striker1.position.x << " " << striker1.position.y << " " << striker2.position.x << " " <<  striker2.position.y << std::endl;
                    update_strikers(pos1[0], pos1[1]);
                    //std::cout << "A striker position " << striker1.position.x << " " << striker1.position.y << " " << striker2.position.x << " " <<  striker2.position.y << std::endl;
                    sf::Vector2f pos = puck.update(striker1, striker2);
                    // if (received) {
                    //     client_direction.x += 1.0f;
                    //     client_direction.y += 1.0f;
                    // }

                    data[i].clear();
                    response[i].clear();
                    //int j = (i == 0) ? 1 : 0;
                    // data[i] << client_direction.x << client_direction.y;
                    response[i] << pos1[0] << pos1[1] << pos;
                    //std::cout << "Client  " << i << " pos updated: " << pos1[i].x << " " \
                                                //<< pos1[i].y << " pos: " << pos.x << " " << pos.y << std::endl;
                }
                send_updates(response);
           // }

            clock.restart();
        }
    }
}