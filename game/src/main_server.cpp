#include "game.h"
#include "server.h"

int main() {
    Server server;
    for (int i = 0; i < 1; ++i) {
        server.handle_connections();
    }
    server.run();
    return 0;
}