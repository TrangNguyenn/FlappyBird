#include "game.h"
#define PAIR_GAP 180 //The gap between 2 pair of pipes


void load_resources_bundles()
{
    load_resource_bundle("resources","flappy_fish.txt");
}

game_data new_game()
{
    game_data result;
    result.fish = new_fish();
    result.game_start = false;
    return result;
}

double next_pair(game_data &game)
{
    // Give the player time to get used to with the game
    double x = sprite_x(game.fish.fish_sprite) + 200; 

    for (int i = 0; i < game.pipe.size(); i++)
    {
        x += PAIR_GAP;
    }
    return x; 
}

void add_pipe_pair(game_data &game)
{
    game.pipe.push_back(new_pipe(next_pair(game),rnd(MIN,MAX)));
}

void remove_pipe(game_data &game, int i)
{
    game.pipe[i] = game.pipe[game.pipe.size() - 1];
    game.pipe.pop_back();
}

void move_pipe(game_data &game, int x)
{
    for (int i = 0; i < game.pipe.size(); i++)
    {
        sprite_set_x(game.pipe[i].down_pipe, sprite_x(game.pipe[i].down_pipe) - x);
        sprite_set_x(game.pipe[i].up_pipe, sprite_x(game.pipe[i].up_pipe) - x);
    }
}

bool check_collision( game_data &game)
{
    // Check if the fish hit the base or float out of the ocean
    if ((sprite_y(game.fish.fish_sprite) >= 400 ) or (sprite_y(game.fish.fish_sprite) <= -100))
        return true;
    
    // Check if the fish hit the base or float out of the surface
    for (int i = 0; i < game.pipe.size(); i++)  
    {
        if ((sprite_collision(game.fish.fish_sprite, game.pipe[i].down_pipe) == true) or (sprite_collision(game.fish.fish_sprite, game.pipe[i].up_pipe) == true))
        return true;
    } 
    return false;
}

void check_death (game_data &game)
{
    if (check_collision(game) and game.fish.life == 0.33)
    {
        game.fish.life -= 0.33;           
    }
    if (check_collision(game) and game.fish.life != 0.33)
    {
        game.fish.life -= 0.33;
        // Reset the fish to the center of screen
        sprite_set_x(game.fish.fish_sprite, (screen_width() - sprite_width(game.fish.fish_sprite))/2);
        sprite_set_y(game.fish.fish_sprite, (screen_height() - sprite_height(game.fish.fish_sprite))/2);
        sprite_set_dy(game.fish.fish_sprite, -2);

        game.pipe.clear();
    }
}

void update_score(game_data &game)
{
    for (int i = 0; i < game.pipe.size(); i++)
    {
        // When the fish is at the middle of 1 pair
        if (( sprite_x(game.fish.fish_sprite) == (sprite_x(game.pipe[i].up_pipe) + sprite_width(game.pipe[i].up_pipe)/2 ) ))
        {
            game.fish.score += 1;
        }
    }
}


void pipe_update(game_data &game)
{
    for (int i = 0; i < game.pipe.size(); i++)
    {
        update_pipe(game.pipe[i]);
        if (sprite_x(game.pipe[i].up_pipe) < (0 - sprite_width(game.pipe[i].up_pipe)))
        {
            remove_pipe(game, i);
        }
    }
}

void display_background(game_data &game)
{
    draw_bitmap("background",0,0,option_to_screen());
    
    if (game.game_start == true)
    {
        for (int i = 0; i < game.pipe.size(); i++)
        {
            draw_pipe(game.pipe[i]);
        }
    }

    draw_bitmap("base", 0, screen_height() - bitmap_height("base"), option_to_screen());
}

void display_homepage(game_data &game)
{   
    if (game.fish.dead == false and game.game_start == false)
    {
        draw_bitmap("message",(screen_width() - bitmap_width("message"))/2, (screen_height() - bitmap_height("message"))/2);
        sprite_set_x(game.fish.fish_sprite, screen_width()/2 - 15);
        sprite_set_y(game.fish.fish_sprite, 300);
        sprite_set_dy(game.fish.fish_sprite, 0);
    }
}

void display_game_over(game_data &game)
{
    if (game.fish.dead == true and game.game_start == false)
    {
        move_pipe(game, 0);
        sprite_set_dy(game.fish.fish_sprite, 0);
        draw_bitmap("gameover", (screen_width() - bitmap_width("gameover"))/2, screen_height()/2);
    }   
}

void start_game (game_data &game)
{
    
    if (game.fish.life > 0)
    {
        move_pipe(game, 1);

        pipe_update(game);

        sprite_set_dy(game.fish.fish_sprite, -2); 

        update_score(game);

        check_death(game);      
        
    }
    if (game.fish.life <= 0)
    {
        game.game_start = false;
        game.fish.dead = true;
    }  
       
}

// Reset everything after the fish dead
void game_over(game_data &game)
{
    game.pipe.clear();
    game.fish.dead = false;
    game.fish.score = 0;
    game.fish.life = 3;
}

void update_game(game_data &game)
{
    update_fish(game.fish);

    while (game.pipe.size() < 10) //Save memory
    {
        add_pipe_pair(game);
    }


    if (game.fish.dead == false and game.game_start == false and game.fish.life == 0.99)
    {
        sprite_set_dy(game.fish.fish_sprite, 0);
        if (mouse_clicked(LEFT_BUTTON))
        {
            game.game_start = true;
        }
    }

    if (game.game_start == true and game.fish.dead == false and game.fish.life > 0)
    {
        start_game(game);
        
    }

    if (game.fish.dead == true and game.game_start == false and game.fish.life <= 0 )
    {
        if(mouse_clicked(LEFT_BUTTON)) //Restart
        {
            game_over(game);
        }
    }
    
}

void draw_game(game_data &game)
{
    clear_screen(COLOR_WHITE);

    display_background(game);

    display_game_over(game);

    display_homepage(game);

    if (game.game_start == true)
    {
        draw_text(to_string(game.fish.score), COLOR_WHITE, "gamefont", 30, screen_width()/2, 456, option_to_screen());
        draw_bitmap("black_heart",(screen_width()-bitmap_width("black_heart"))/2, 10, option_to_screen());
        draw_bitmap("heart", (screen_width()-bitmap_width("heart"))/2, 10, option_part_bmp(0,0,game.fish.life*bitmap_width("black_heart"),bitmap_height("heart"),option_to_screen()));
    }

    draw_fish(game.fish);

    refresh_screen(60);
}

