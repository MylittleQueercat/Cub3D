#include "../include/cub3d.h"

// static void init_test_map(t_club *club)
// {
//     static char *grid[] = {
//         "1111111111",
//         "1000000001",
//         "1000000001",
//         "1000100001",
//         "1000000101",
//         "1000000001",
//         "1000110001",
//         "1000000001",
//         "1111111111",
//         NULL
//     };

//     club->map.grid = grid;
//     club->map.height = 9;          // 上面有 9 行
//     club->map.width = 10;          // 每行 10 个字符
// }

void init_club_defaults(t_club *club)
{
    int i;

	club->file = NULL;
	club->mlx = NULL;
	club->win = NULL;
	club->img.img = NULL;
	club->img.addr = NULL;
	club->map.grid = NULL;
	club->map.width = 0;
	club->map.height = 0;
	club->floor_color = -1;
	club->ceiling_color = -1;
	club->sprites = NULL;
	club->sprite_count = 0;
	club->sprite_jump = 0;
	club->found_count = 0;
	club->game_won = 0;
	club->win_img.img = NULL;
	club->win_img.addr = NULL;
	club->win_loaded = 0;
	club->doors = NULL;
	club->door_count = 0;
	ft_bzero(&club->door_tex, sizeof(t_tex));
	club->door_tex.path = ft_strdup("xpms/door_BRUNE.xpm");
	ft_bzero(&club->door_open_tex, sizeof(t_tex));
	club->door_open_tex.path = ft_strdup("xpms/door_BRUNE.xpm");
	club->mouse_last_x = WIDTH / 2;
	club->mouse_in_window = 0;
	club->show_minimap = 1;
	club->mouse_left = 0;
	club->mouse_sens = 0.003;
	club->key_w = 0;
	club->key_a = 0;
	club->key_s = 0;
	club->key_d = 0;
	club->key_left = 0;
	club->key_right = 0;
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
		club->tex[i].path = NULL;
		i++;
	}
	i = 0;
	while (i < SPRITE_TYPES)
	{
		club->sprite_textures[i].img = NULL;
		club->sprite_textures[i].addr = NULL;
		club->sprite_textures[i].bpp = 0;
		club->sprite_textures[i].line_len = 0;
		club->sprite_textures[i].endian = 0;
		club->sprite_textures[i].width = 0;
		club->sprite_textures[i].height = 0;
		i++;
	}
}

// static void init_player(t_club *club)
// {
//     club->player.x = 4.5;
//     club->player.y = 4.5;
//     club->player.dir_x = -1.0;
//     club->player.dir_y = 0.0;
//     club->player.plane_x = 0.0;
//     club->player.plane_y = 0.66;
// }

// int init_club(t_club *club)
// {
//     init_club_defaults(club);
//     club->mlx = mlx_init();
//     if (!club->mlx)
//         return (1);
//     club->win = mlx_new_window(club->mlx, WIDTH, HEIGHT, "PINK PONY CLUB");
//     if (!club->win)
//         return (1);
//     if (init_image(club))
//         return (1);

//     // 测试地图（之后换成 parser）
//     //init_test_map(club);

//     club->ceiling_color = 0xFF8AD6; // 粉1
//     club->floor_color = 0x3B0F5F;   // 紫
//     if (load_all_textures(club))
//         return (1);
//     init_player(club);
//     return (0);
// }

int init_club(t_club *club)
{
	club->mlx = mlx_init();
	if (!club->mlx)
		return (1);
	club->win = mlx_new_window(club->mlx, WIDTH, HEIGHT, "PINK PONY CLUB");
	if (!club->win)
		return (1);
	if (load_win_banner(club))
        return (err_msg("failed to load win banner"), 1);
	if (init_image(club))
		return (1);
	if (!init_doors(club))
			return (1);
	if (!init_sprits(club))
		return (1);
	//printf("number sprite : %d\n", club->sprite_count);
    return (0);
}

