#ifndef FLAPPY_FISH_PLAYER
#define FLAPPY_FISH_PLAYER

#include "splashkit.h"

//Track the fish status and movement
struct fish_data
{
    sprite fish_sprite; // Track position and movement
    int    score; //Game score
    bool   dead;  // Fish status
    double    life; // Fish lives to allow the fish to be realive
};

//Creates a new fish in the centre of the screen with the default bitmap.
fish_data new_fish();

// Allow player to move the fish
void handle_input(fish_data &fish);

// Draw the fish to the screen
void draw_fish(const fish_data &fish);

// Update the fish
void update_fish(fish_data &fish_to_update);

#endif