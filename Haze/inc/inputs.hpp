/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-erwan.gonzales
** File description:
** inputs
*/

#pragma once

namespace Haze
{
    enum InputType {
        NO,
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,

        NUMKEY_0,
        NUMKEY_1,
        NUMKEY_2,
        NUMKEY_3,
        NUMKEY_4,
        NUMKEY_5,
        NUMKEY_6,
        NUMKEY_7,
        NUMKEY_8,
        NUMKEY_9,

        KEY_DOT,

        KEY_ESC,
        KEY_ENTER_INPUT,
        KEY_BACK,
        KEY_TAB,
        KEY_SPACE,

        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,

        KEY_UP_ARROW,
        KEY_DOWN_ARROW,
        KEY_LEFT_ARROW,
        KEY_RIGHT_ARROW
    };

    enum MouseType {
        NOTHING,
        RELEASED,
        PRESSED
    };
}
