#include "game.h"
#include "server.h"

int main() {
    Server server;
    Game game;
    // Handle single client only for now
    for (int i = 0; i < 1; ++i) {
        server.handle_connections();
    }
    server.run(game);
    return 0;
}