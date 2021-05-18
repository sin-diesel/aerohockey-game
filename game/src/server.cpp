#include "server.h"
#include "dynamic.h"
Server::Server():     
    puck(static_cast<float>(PUCK_MASS), static_cast<float>(PUCK_RADIUS)),
    striker1(static_cast<float>(STRIKER_MASS), static_cast<float>(STRIKER_RADIUS)),
    striker2(static_cast<float>(STRIKER_MASS), static_cast<float>(STRIKER_RADIUS))  {
    port = PORT;
    score.x = 0, score.y = 0;
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
    response << new_port << client_number;
    socket.send(response, client_addr, client_port);
}

std::vector<bool> Server::get_updates(std::vector<sf::Packet>& data) //receives data about strikers moving from clients
{
    sf::IpAddress client_address;
    unsigned short client_port;
    std::vector<bool> received(2);
    received[0] = false, received[1] = false;
    // here we receive not from the main server socket, but instead from client socket
    //client_selector.wait()
    if (client_selector.wait(sf::milliseconds(PINGSERVER))) {
        for (int i = 0; i < 2; ++i) {
            if (client_selector.isReady(*(client_sockets[i]))) {
                client_sockets[i]->receive(data[i], client_address, client_port);
                std::cout << "Received from: " << std::endl;
                std::cout << client_address << std::endl << client_port << std::endl;
                received[i] = true;
            } else {
                //!!!!! std::cerr << "Error receiving packet from client. " << std::endl;
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

    return received;
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
    if ((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y) <= STRIKER_RADIUS * STRIKER_RADIUS) {
        pos1 = striker1.get_coord(), pos2 = striker2.get_coord();
        //std::cout << "ASSERT" << std::endl;
    }
    striker1.calculate_speed(pos1);
    striker2.calculate_speed(pos2);
    striker1.set_coord(pos1);
    striker2.set_coord(pos2);
}

bool Server::send_updates(sf::Packet& data, int i) // calculates new cooridinates of puck and strikers and sends to clients
{
    if (client_sockets[i]->send(data, adresses[i], ports[i]) != sf::Socket::Done) {
        std::cerr << "Error sending data to client. " << std::endl;
        std::cerr << std::endl;
        return false;
    }
    return true;
}

void Server::run() {
    //sf::Time network_update_time = sf::milliseconds(PING);
    sf::Clock clock;
    sf::Time elapsed;

    std::vector<sf::Packet> data;
    for (int i = 0; i < 2; ++i) {
        data.push_back(sf::Packet());
    }
    
    sf::Packet response;
    sf::Vector2f pos1[2];

    while (1) {
        std::vector<bool> received;
        received.push_back(true), received.push_back(true);
        elapsed = clock.getElapsedTime();
        //if (elapsed > sf::milliseconds(PINGSERVER)) {
            received = get_updates(data);
                for (int i = 0; i < 2; ++i) {
                    if (received[i]) {
                        data[i] >> pos1[i];
                        update_strikers(pos1[0], pos1[1]);
                        puck.update(striker1, striker2);
                        sf::Vector2i score = update_score(puck.check_score());
                        data[i].clear();
                        response.clear();
                        std::cout << "ST1: " << pos1[0].x << " " << pos1[0].y << std::endl << "ST2: " << pos1[1].x << " " << pos1[1].y << std::endl << "PUCK: " << puck.get_coord().x << " " << puck.get_coord().y << std:: endl << score.x << " " << score.y << std::endl;
                        response << pos1[0] << pos1[1] << puck.get_coord() << score;
                        send_updates(response, i);

                    }
                }
            clock.restart();
        //}
    }
}

sf::Vector2i Server::update_score(int side) {
    if (side == 0)
        return score;
    (side == 2) ? score.x++ : score.y++;
    return score;
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
