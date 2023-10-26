//
// Created by erwan on 10/15/23.
//

#ifndef D2B97CFD_7B7F_4CA9_BEC5_C131DC486E47
#define D2B97CFD_7B7F_4CA9_BEC5_C131DC486E47


#include "../protocol.h"
#include "Cooldown.h"
#include <componentData.hpp>
#include <data.h>
#include <haze-core.hpp>
#include <net_data_channel.h>

using namespace asio::ip;
using namespace std::chrono_literals;

class Player {
public:
    struct Remote {
        asio::ip::udp::endpoint endpoint;
        Cooldown activityCd{10s};

        explicit Remote(udp::endpoint endpoint) : endpoint(std::move(endpoint)) { activityCd.Activate(); }
    };

    Player(Haze::Engine &engine, network::data_channel<protocol::data> &channel, uint32_t id);
    void build();
    void update();
    void send();
    void sendUpdate();

public:
    std::unique_ptr<Remote> _remote = nullptr;
    Haze::Entity *_entity = nullptr;

    uint32_t _id = 0;
    uint32_t _score = 0;


private:
    Haze::Engine &_engine;
    network::data_channel<protocol::data> &_channel;
};


#endif /* D2B97CFD_7B7F_4CA9_BEC5_C131DC486E47 */
