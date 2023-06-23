#include <iostream>
#include "application/app.h"
#include "config/config.h"

void sig(int) {
    throw std::runtime_error("Program has been terminated by CTRL + C");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments" << std::endl;
        return 1;
    }

    signal(SIGTERM, sig);
    signal(SIGINT, sig);
    config _config;

    try {
        _config.loadConfig(argv[1]);
        app _app(_config);
        _app.run();
    } catch (const std::exception &e) {
        if (std::cin.eof()) {
            return 1;
        }
        std::cerr << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Běž se učit!" << std::endl;
    }

    return 0;
}
