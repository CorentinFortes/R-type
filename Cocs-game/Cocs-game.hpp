/*
** EPITECH PROJECT, 2023
** cpp r-type
** File description:
** Cocs-game.hpp
*/

#pragma once

#include "Player.h"
#include "data.h"
#include "net_data_channel.h"
#include "net_server.h"
#include "protocol.h"
#include "Ball.h"
#include "Cooldown.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "../Igame.hpp"

class Cocs_game : public Igame
{
public:
    Cocs_game(asio::io_context &context);
    ~Cocs_game();

    void start() override;
    void stop() override;
    void update() override;
    void sendUpdate();

    void onReceive(udp::endpoint from, network::datagram<protocol::data> content);
    void sendEverything(udp::endpoint &to);
    [[nodiscard]] asio::ip::udp::endpoint getEndpoint() const override;

    void updateMap();// TODO : map who generate itself and destroy itself
    void createMap();
    void checkInactiveClients();

    uint32_t getPlayerID(const asio::ip::udp::endpoint &endpoint);
private:
    Haze::Engine _engine;
    network::data_channel<protocol::data> _channel;

    bool _running;
    std::vector<Haze::Entity *> _entities;
    std::vector<std::unique_ptr<Racket>> _players;
    std::unique_ptr<Racket> player;
    std::unique_ptr<Ball> _ball;
};

