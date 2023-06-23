//
// Created by prokoseb on 3.6.23.
//

#ifndef TOWER_DEFENSE_LOAD_ERROR_H
#define TOWER_DEFENSE_LOAD_ERROR_H

#include <exception>
#include <string>
#include <utility>

/**
 * @brief Exception that is thrown when we load the game and something goes wrong
 */
class load_error : public std::exception {
public:
    explicit load_error(std::string msg) : _msg(std::move(msg)) {}

    const char *what() const noexcept override {
        return _msg.c_str();
    }

private:
    std::string _msg;
};

#endif //TOWER_DEFENSE_LOAD_ERROR_H
