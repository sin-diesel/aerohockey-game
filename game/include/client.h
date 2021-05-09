#include "game.h"


class Client {
private:
    sf::IpAddress addr;
    unsigned short port;
    sf::UdpSocket socket;
public:
    Client();
    ~Client();
    void connect(sf::IpAddress server_addr);
    bool send(sf::Packet& packet, sf::IpAddress server_addr);
};

