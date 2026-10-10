#include <iostream>
#include <cassert>
#include "core/types.hpp"

int main() {
    uint16_t player1_input = 0;
    player1_input |= INPUT_UP;
    player1_input |= INPUT_A;

    assert((player1_input & INPUT_UP) != 0);
    assert((player1_input & INPUT_DOWN) == 0);
    assert((player1_input & INPUT_A) != 0);

    Vec2 pos;
    pos.x = 100;
    pos.y = 200;
    Vec2 vel;
    vel.x = 5;
    vel.y = -10;
    
    pos.x += vel.x;
    pos.y += vel.y;

    assert(pos.x == 105);
    assert(pos.y == 190);

    std::cout << "All types and bitmask tests passed successfully!" << std::endl;

    return 0;
}