#include "server.h"
#include "dynamic.h"
Server::Server():     
    puck(static_cast<float>(PUCK_MASS), static_cast<float>(PUCK_RADIUS), CENTER_X, CENTER_Y, 0),
    striker1(static_cast<float>(STRIKER_MASS), static_cast<float>(STRIKER_RADIUS), CENTER_X - 200, CENTER_Y, 1),
    striker2(static_cast<float>(STRIKER_MASS), static_cast<float>(STRIKER_RADIUS), CENTER_X + 200, CENTER_Y, 2),
    port(PORT),
    addr(sf::IpAddress::LocalHost)  {
    if (socket.bind(PORT) != sf::UdpSocket::Done) {
        std::cerr << "Error binding server socket. " << std::endl;
    }
    socket.setBlocking(true);
    for (int i = 0; i < 2; ++i) { 
        sf::UdpSocket* client_socket = new sf::UdpSocket();
        client_sockets.push_back(client_socket);

        if (client_sockets[i]->bind(sf::Socket::AnyPort) != sf::UdpSocket::Done) {
            std::cerr << "Error binding client socket on server. " << std::endl;
        }

        client_sockets[i]->setBlocking(true);
        client_selector.add(*(client_sockets[i]));
    }
}

Server::~Server() {
    socket.unbind();
    for (int i = 0; i < client_sockets.size(); ++i)
        client_sockets[i]->unbind();
    for (int i = 0; i < 2; ++i)
        delete client_sockets[i];
}

void Server::handle_connections(int client_number) {

    sf::Packet connection_info;
    sf::IpAddress client_addr;
    unsigned short client_port;
    
    std::cout << "Waiting for incoming connection from client..." << std::endl; 
    socket.receive(connection_info, client_addr, client_port);
    
    adresses.push_back(client_addr); //save client's adress
    ports.push_back(client_port);    //save client's port
    bool temp;
    connection_info >> temp;
    keyboard_control[client_number] = temp;
    connection_info.clear();
    std::cout << "Packet from client received " << std::endl;
    std::cout << "Client addr: " << client_addr << std::endl;
    std::cout << "Client port: " << client_port << std::endl;

    unsigned short new_port = client_sockets[client_number]->getLocalPort();
    std::cout << "Port distrubuted for new client: " << new_port << std::endl;
    
    sf::Packet response;
    response << new_port << client_number;
    socket.send(response, client_addr, client_port);
    response.clear();
}

std::vector<bool> Server::get_updates(std::vector<sf::Packet>& data) //receives data about strikers moving from clients
{
    sf::IpAddress client_address;
    unsigned short client_port;
    std::vector<bool> received(2);
    received[0] = false, received[1] = false;
    if (client_selector.wait(sf::milliseconds(PINGSERVER))) {
        for (int i = 0; i < 2; ++i) {
            if (client_selector.isReady(*(client_sockets[i]))) {
                client_sockets[i]->receive(data[i], client_address, client_port);
                //std::cout << "Received from: " << std::endl;
                //std::cout << client_address << std::endl << client_port << std::endl;
                received[i] = true;
            } else {
                //std::cerr << "Error receiving packet from client. " << std::endl;
                //std::cerr << std::endl;
            }
        }
    }
    return received;
}

bool Server::send_updates(sf::Packet& data, int i)
{
    if (client_sockets[i]->send(data, adresses[i], ports[i]) != sf::Socket::Done) {
        std::cerr << "Error sending data to client. " << std::endl;
        std::cerr << std::endl;
        return false;
    }
    //std::cout << "SEND TO " << i << " " << adresses[i] << " " << ports[i] << std::endl;
    return true;
}

void Server::mouse_update_strikers(sf::Vector2f pos, int i)
{
    ServerDynamicObject& striker = ((i == 0) ? striker1 : striker2);
    if (pos.x + STRIKER_RADIUS > ((striker.get_number() == 2) ? MAX_POS_X : CENTER_X))
        pos.x = ((striker.get_number() == 2) ? MAX_POS_X : CENTER_X) - STRIKER_RADIUS;
    if (pos.x - STRIKER_RADIUS < ((striker.get_number() == 1) ? MIN_POS_X : CENTER_X))
        pos.x = ((striker.get_number() == 1) ? MIN_POS_X : CENTER_X) + STRIKER_RADIUS;
    if (pos.y + STRIKER_RADIUS > MAX_POS_Y)
        pos.y = MAX_POS_Y - STRIKER_RADIUS;
    if (pos.y - STRIKER_RADIUS < MIN_POS_Y)
        pos.y = MIN_POS_Y + STRIKER_RADIUS;
    striker.calculate_speed(pos);
    striker.set_coord(pos);
}

void Server::keyboard_update_strikers_position()
{
    striker1.keyboard_update_speed();
    striker2.keyboard_update_speed();
}

sf::Vector2i Server::update_score(int side) {
    if (side == 0)
        return score;
    (side == 2) ? score.x++ : score.y++;
    return score;
}

void Server::update_and_send(int i)
{
    puck.update(striker1, striker2);
    int side = puck.check_score();
    sf::Vector2i score = update_score(side);
    //std::cout << "ST1: " << striker1.get_coord().x << " " << striker1.get_coord().y << std::endl << "ST2: " << striker2.get_coord().x << " " << striker2.get_coord().y << std::endl << "PUCK: " << puck.get_coord().x << " " << puck.get_coord().y << std:: endl << score.x << " " << score.y << std::endl;
    sf::Packet response;
    response << striker1.get_coord() << striker2.get_coord() << puck.get_coord() << score << false;
    send_updates(response, i);
    response.clear();
    //if (side != 0)
        //time_out();
}

void Server::time_out()
{
    sf::Vector2f pos(CENTER_X - 200, CENTER_Y);
    striker1.set_coord(pos);
    pos.x += 400;
    striker2.set_coord(pos);
    sf::Packet response;
    response << striker1.get_coord() << striker2.get_coord() << puck.get_coord() << true;
    send_updates(response, 0);
    send_updates(response, 1);
    response.clear();
}

void Server::run() {
    std::vector<sf::Packet> data = {sf::Packet(), sf::Packet()};
    std::vector<std::vector<int>> key(2, std::vector<int>(4, -1));
    sf::Vector2f pos1[2];
    int side;
    while (1) {
        std::vector<bool> received = {true, true};
        received = get_updates(data);
        for (int i = 0; i < 2; ++i) {
            if (received[i]) {
                if (!keyboard_control[i]) {
                    data[i] >> pos1[i];
                    mouse_update_strikers(pos1[i], i);
                    update_and_send(i);
                } else {
                    data[i] >> key[i][0] >> key[i][1] >> key[i][2] >> key[i][3];
                    //std::cout << "RECEIVED " << key[i][0] << " " << key[i][1] << " " << key[i][2] << " " << key[i][3] << std::endl;
                    (i == 0) ? striker1.keyboard_change_speed(key[i]) : striker2.keyboard_change_speed(key[i]);
                }
            }
            data[i].clear();
            if(keyboard_control[i]) {
                keyboard_update_strikers_position();
                update_and_send(i);
            }
        }
    }
}


sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& pos) {
    return packet << pos.x << pos.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& pos) {
    return packet >> pos.x >> pos.y;
}

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2i& pos) {
    return packet << pos.x << pos.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2i& pos) {
    return packet >> pos.x >> pos.y;
}
