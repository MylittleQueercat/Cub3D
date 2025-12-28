#include "../include/cub3d.h"

void    mm_draw_square(t_img *img, int x, int y, int size, int color)
{
    int sx;
    int sy;

    sy = 0;
    while (sy < size)
    {
        sx = 0;
        while (sx < size)
        {
            put_pixel(img, x + sx, y + sy, color);
            sx++;
        }
        sy++;
    }
}

void    mm_draw_player_pony(t_img *img, int cx, int cy, int tile)
{
    int radius;
    int r2;
    int x;
    int y;

    // 半径：大约占一格的 1/3
    radius = tile / 3;
    if (radius < 3)
        radius = 3;
    r2 = radius * radius;
    // 以 (cx, cy) 为圆心，画一个实心小圆
    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= r2)
                put_pixel(img, cx + x, cy + y, MM_PLAYER);
            x++;
        }
        y++;
    }
}

void    mm_draw_sprite(t_img *img, int cx, int cy, int tile)
{
    int radius;
    int r2;
    int x;
    int y;

    // 精灵在 minimap 上稍小一点
    radius = tile / 4;
    if (radius < 2)
        radius = 2;
    r2 = radius * radius;

    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= r2)
                put_pixel(img, cx + x, cy + y, MM_SPRITE);
            x++;
        }
        y++;
    }
}


void    render_minimap(t_club *club)
{
    int     x;
    int     y;
    int     tile;
    int     map_x;
    int     map_y;
    char    **g;

    tile = 17;
    y = 0;
    g = club->map.grid;
    while (y < club->map.height)
    {
        x = 0;
        while (x < club->map.width - 1)
        {
            if (g[y][x] == '1')
                mm_draw_square(&club->img, x * tile, y * tile, tile, MM_WALL);
            else if (g[y][x] == 'D')
                mm_draw_square(&club->img, x * tile, y * tile, tile, MM_DOOR);
            else
                mm_draw_square(&club->img, x * tile, y * tile, tile, MM_BG);
            x++;
        }
        y++;
    }
    map_x = (int)(club->player.x * tile);
    map_y = (int)(club->player.y * tile);
    mm_draw_player_pony(&club->img, map_x, map_y, tile);
    int i = 0;
    while (i < club->sprite_count)
    {
        if (club->sprites[i].found)
        {
            int sx = (int)(club->sprites[i].x * tile);
            int sy = (int)(club->sprites[i].y * tile);
            mm_draw_sprite(&club->img, sx, sy, tile);
        }
        i++;
    }
}