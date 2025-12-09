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

void    mm_draw_player_pony(t_img *img, int px, int py)
{
    put_pixel(img, px + 1, py + 0, MM_PLAYER);
    put_pixel(img, px + 2, py + 0, MM_PLAYER);
    put_pixel(img, px + 3, py + 0, MM_PLAYER);
    put_pixel(img, px + 0, py + 1, MM_PLAYER);
    put_pixel(img, px + 1, py + 1, MM_PLAYER);
    put_pixel(img, px + 2, py + 1, MM_PLAYER);
    put_pixel(img, px + 3, py + 1, MM_PLAYER);
    put_pixel(img, px + 4, py + 1, MM_PLAYER);
    put_pixel(img, px + 2, py + 2, MM_PLAYER);
    put_pixel(img, px + 3, py + 2, MM_PLAYER);
    put_pixel(img, px + 4, py + 2, MM_PLAYER);
    put_pixel(img, px + 5, py + 2, MM_PLAYER);
    put_pixel(img, px + 1, py + 3, MM_PLAYER);
    put_pixel(img, px + 2, py + 3, MM_PLAYER);
    put_pixel(img, px + 0, py + 4, MM_PLAYER);
    put_pixel(img, px + 1, py + 4, MM_PLAYER);
    put_pixel(img, px + 3, py + 4, MM_PLAYER);
    put_pixel(img, px + 4, py + 4, MM_PLAYER);
}

void    render_minimap(t_club *club)
{
    int     x;
    int     y;
    int     tile;
    int     map_x;
    int     map_y;
    char    **g;

    tile = 13;
    y = 0;
    g = club->map.grid;
    while (y < club->map.height)
    {
        x = 0;
        while (x < club->map.width)
        {
            if (g[y][x] == '1')
                mm_draw_square(&club->img, x * tile, y * tile, tile, MM_WALL);
            else
                mm_draw_square(&club->img, x * tile, y * tile, tile, MM_BG);
            x++;
        }
        y++;
    }
    // 玩家位置
    map_x = (int)(club->player.x * tile);
    map_y = (int)(club->player.y * tile);
    mm_draw_player_pony(&club->img, map_x, map_y);
}
