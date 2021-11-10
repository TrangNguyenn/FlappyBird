#include "fish.h"


fish_data new_fish()
{
    fish_data result;
    bitmap default_bitmap = bitmap_named("fish");

    result.fish_sprite = create_sprite(default_bitmap);
    result.score = 0;
    result.dead = false;
    result.life = 0.99; // At the beginning, the fish have 3 lives

    sprite_set_x(result.fish_sprite, (screen_width() - sprite_width(result.fish_sprite))/2);
    sprite_set_y(result.fish_sprite, (screen_height() - sprite_height(result.fish_sprite))/2);

    return result;
}

void handle_input(fish_data &fish)
{
    if (fish.dead == false)
    {
        if (mouse_clicked(LEFT_BUTTON))
        {
            sprite_set_dy(fish.fish_sprite, 50);
        }
    }
}

void draw_fish(const fish_data &fish)
{
    draw_sprite(fish.fish_sprite);
}

void update_fish(fish_data &fish_to_update)
{
    update_sprite(fish_to_update.fish_sprite);
}