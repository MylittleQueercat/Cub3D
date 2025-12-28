#include "../include/cub3d.h"

// void draw_win_text(t_club *club)
// {
//     char buf[64];

//     if (club->sprite_count <= 0)
//         return ;

//     if (club->game_won)
//     {
//         mlx_string_put(club->mlx, club->win, WIDTH/2 - 40, HEIGHT/2, 0xFFFFFF, "YOU WIN!");
//         return ;
//     }
//     snprintf(buf, sizeof(buf), "%d / %d found", club->found_count, club->sprite_count);
//     mlx_string_put(club->mlx, club->win, 20, 20, 0xFFFFFF, buf);
// }

int load_win_banner(t_club *c)
{
    if (c->win_loaded)
        return (0);

    c->win_img.img = mlx_xpm_file_to_image(c->mlx, "xpms/you_win.xpm",
                                          &c->win_img.width, &c->win_img.height);
    if (!c->win_img.img)
        return (1);

    c->win_img.addr = mlx_get_data_addr(c->win_img.img, &c->win_img.bpp,
                                        &c->win_img.line_len, &c->win_img.endian);
    c->win_loaded = 1;
    return (0);
}
