#ifndef FLAPPY_BIRD_GAME
#define FLAPPY_BIRD_GAME

#include "pipe.h"
#include "fish.h"

#include <vector>

using std::vector;
using namespace std;

struct game_data
{
    fish_data         fish;
    vector<pipe_data> pipe;
    bool              game_start;
};

// Create a new game with new fish
game_data new_game();

// Load resources such as image, font,...
void load_resources_bundles();

// To ensure the gap between 2 pipe pair
double next_pair(game_data &game);

// Add a pipe pair
void add_pipe_pair(game_data &game);

// Remove the pipe pair when it is far from the fish
void remove_pipe(game_data &game, int i);

// Gradually moving pipes to the left
void move_pipe(game_data &game, int x);

// Check if the fish hits the pipe, or base or float out of surface
bool check_collision( const fish_data &fish, pipe_data &pipe);

//Check if the fish is dead
void check_death (game_data &game);

//Update score when the fish moves through a pipe pair
void update_score(game_data &game);

// Update pipes
void pipe_update(game_data &game);

// Display the background
void display_background(game_data &game);

// Display game over text when the fish is dead
void display_game_over(game_data &game);

// Display the homepage at the beginning
void display_homepage(game_data &game);

//Start the game
void start_game(game_data &game);

// Reset when game over
void game_over(game_data &game);

// Update the game
void update_game(game_data &game);

// Draw the game to screen
void draw_game(game_data &game);


#endif