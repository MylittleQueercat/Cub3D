#include "../include/cub3d.h"

static void init_test_map(t_club *club)
{
    static char *grid[] = {
        "1111111111",
        "1000000001",
        "1000000001",
        "1000100001",
        "1000000101",
        "1000000001",
        "1000110001",
        "1000000001",
        "1111111111",
        NULL
    };

    club->map.grid = grid;
    club->map.height = 9;          // 上面有 9 行
    club->map.width = 10;          // 每行 10 个字符
}

static void init_club_defaults(t_club *club)
{
    int i;

    club->mlx = NULL;
    club->win = NULL;
    club->img.img = NULL;
    club->img.addr = NULL;
    club->map.grid = NULL;
    club->map.width = 0;
    club->map.height = 0;
    club->floor_color = 0;
    club->ceiling_color = 0;

    // 初始化纹理数组
    i = 0;
    while (i < TEX_COUNT)
    {
        club->tex[i].img = NULL;
        club->tex[i].addr = NULL;
        club->tex[i].bpp = 0;
        club->tex[i].line_len = 0;
        club->tex[i].endian = 0;
        club->tex[i].width = 0;
        club->tex[i].height = 0;
        i++;
    }
}

static void init_player(t_club *club)
{
    club->player.x = 4.5;
    club->player.y = 4.5;
    club->player.dir_x = -1.0;
    club->player.dir_y = 0.0;
    club->player.plane_x = 0.0;
    club->player.plane_y = 0.66;
}

int init_club(t_club *club)
{
    init_club_defaults(club);
    club->mlx = mlx_init();
    if (!club->mlx)
        return (1);
    club->win = mlx_new_window(club->mlx, WIDTH, HEIGHT, "PINK PONY CLUB");
    if (!club->win)
        return (1);
    if (init_image(club))
        return (1);

    // 测试地图（之后换成 parser）
    init_test_map(club);

    club->ceiling_color = 0xFF8AD6; // 粉1
    club->floor_color = 0x3B0F5F;   // 紫
    if (load_all_textures(club))
        return (1);
    init_player(club);
    return (0);
}
