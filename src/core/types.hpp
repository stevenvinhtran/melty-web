#pragma once
#include <cstdint>

enum InputButtons : uint16_t {
    INPUT_UP = 1 << 0,
    INPUT_DOWN = 1 << 1,
    INPUT_LEFT = 1 << 2,
    INPUT_RIGHT = 1 << 3,
    INPUT_A = 1 << 4,
    INPUT_B = 1 << 5,
    INPUT_C = 1 << 6,
    INPUT_D = 1 << 7,
    INPUT_E = 1 << 8,
    INPUT_START = 1 << 9,
    INPUT_FN1 = 1 << 10,
    INPUT_FN2 = 1 << 11,
    INPUT_AB = 1 << 12
};

struct Vec2 {
    int32_t x;
    int32_t y;
};