//
// Created by erwan on 9/29/23.
//

#pragma once

#include <cstdint>

enum class Protocol : std::uint32_t {
    // Request
    create_room,
    get_rooms,
    join_room,
    leave_room,
    start_room,

    // Response
    data_channel,
};


enum class UDPProtocol : std::uint32_t {
    alive,
    acknowledge,
};