#include "game.h"
#include "server.h"

int main() {
    Server server;
    Game game;
    // Handle two client only for now
    for (int client_number = 0; client_number < 2; ++client_number) {
        server.handle_connections(client_number);
    }
    server.run(game);
    return 0;
}