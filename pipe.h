#ifndef FLAPPY_FISH_PIPE
#define FLAPPY_FISH_PIPE

#include "splashkit.h"
#define MAX 400 // To ensure there is always a gap between down pipe and the top edge
#define MIN 112 // To ensure there is always a gap between up pipe and base
#define GAP 108 //The gap betweeen up and down pipes

// Track the pipe data
struct pipe_data
{
    sprite down_pipe; // Track position and movement of down pipe
    sprite up_pipe; // Track position and movement of up pipe
};

enum pipe_kind
{
    UP,
    DOWN
};

//Create the new pipe to the screen
pipe_data new_pipe(double x, double y);

// Draw pipes
void draw_pipe(const pipe_data &pipe);

// Update pipes
void update_pipe(pipe_data &pipe_to_update);

#endif