//
// Created by erwan on 9/29/23.
//

#pragma once

#include <cstdint>

namespace com {
    enum class lobby : std::uint8_t {
        // Request
        create_room,
        get_rooms,
        join_room,
        leave_room,
        start_room,

        // Response
        ok,
        ko,
        rooms,
        data,
    };
}

enum class UDPProtocol : std::uint32_t {
    alive,
    acknowledge,
};