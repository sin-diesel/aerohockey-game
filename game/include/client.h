#include "library.h"

class Client {
    private:

        sf::IpAddress addr;
        unsigned short port;
        sf::UdpSocket socket;
        sf::IpAddress server_addr;
        unsigned short server_port;
        int number;

    public:
        Client();
        ~Client();
        int get_number();
        void set_number(int num);
        void connect(sf::IpAddress server_addr);
        unsigned short get_port();
        sf::Packet process_input();
        bool send_updates(sf::Packet& packet);
        bool receive_updates(sf::Packet& packet, sf::IpAddress& server_addr, unsigned short& server_port);
};


sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& pos);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& pos);

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2i& pos);

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2i& pos);
