#include "game.h"


class Client {
private:

    sf::IpAddress addr;
    unsigned short port;
    sf::UdpSocket socket;
    int number;
    
public:

    Client();
    ~Client();

    void connect(sf::IpAddress server_addr);
    unsigned short get_port();
    sf::Packet process_input();
    sf::Time get_update_time(Game& game);

    bool send_updates(sf::Packet& packet, sf::IpAddress server_addr, unsigned short server_port);
    bool receive_updates(sf::Packet& packet, sf::IpAddress& server_addr, unsigned short& server_port);
};

