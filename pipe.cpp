#include "pipe.h"

bitmap pipe_bitmap (pipe_kind kind)
{
    switch (kind)
    {
    case UP:
        return bitmap_named("pipe-up");
    case DOWN:
        return bitmap_named("pipe-down");
    }
    return 0;
}

pipe_data new_pipe(double x, double y)
{
    pipe_data result;
    bitmap up_pipe_bitmap = pipe_bitmap(UP);
    result.up_pipe = create_sprite(up_pipe_bitmap);

    bitmap down_pipe_bitmap = pipe_bitmap(DOWN);
    result.down_pipe = create_sprite(down_pipe_bitmap); 

    sprite_set_x(result.down_pipe, x);
    sprite_set_y(result.down_pipe, y);

    sprite_set_x(result.up_pipe, x);
    sprite_set_y(result.up_pipe, y - GAP - sprite_height(result.up_pipe));

    return result;
}

void draw_pipe(const pipe_data &pipe)
{
    draw_sprite(pipe.down_pipe);
    draw_sprite(pipe.up_pipe);
}

void update_pipe(pipe_data &pipe_to_update)
{
    update_sprite(pipe_to_update.down_pipe);
    update_sprite(pipe_to_update.up_pipe);
}

