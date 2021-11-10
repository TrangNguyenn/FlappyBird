#include "splashkit.h"
#include "game.h"

int main()
{

    load_resources_bundles();

    open_window("Flappy Fish",bitmap_width("background"), bitmap_height("background"));
    
    game_data my_game;
    my_game = new_game();


    while (not quit_requested())
    {
        process_events();

        handle_input(my_game.fish);

        draw_game(my_game);

        update_game(my_game);
    }
    return 0;
}