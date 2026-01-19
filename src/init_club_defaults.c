#include "../include/cub3d.h"

static void	init_ptrs_defaults(t_club *club)
{
	club->file = NULL;
	club->mlx = NULL;
	club->win = NULL;
	club->img.img = NULL;
	club->img.addr = NULL;
	club->win_img.img = NULL;
	club->win_img.addr = NULL;
	club->map.grid = NULL;
	club->sprites = NULL;
	club->doors = NULL;
}

static void	init_values_defaults(t_club *club)
{
	club->map.width = 0;
	club->map.height = 0;
	club->floor_color = 0;
	club->ceiling_color = 0;
	club->sprite_count = 0;
	club->sprite_jump = 0;
	club->found_count = 0;
	club->game_won = 0;
	club->win_loaded = 0;
	club->door_count = 0;
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
}

static void	init_door_tex_defaults(t_club *club)
{
	ft_bzero(&club->door_tex, sizeof(t_tex));
	club->door_tex.path = ft_strdup("xpms/door2.xpm");
	ft_bzero(&club->door_open_tex, sizeof(t_tex));
	club->door_open_tex.path = ft_strdup("xpms/door2.xpm");
}

static void	init_tex_arrays_defaults(t_club *club)
{
	ft_bzero(club->tex, sizeof(club->tex));
	ft_bzero(club->sprite_textures, sizeof(club->sprite_textures));
}

// static void	init_tex_arrays_defaults(t_club *club)
// {
// 	int	i;

// 	i = 0;
// 	while (i < TEX_COUNT)
// 	{
// 		club->tex[i].img = NULL;
// 		club->tex[i].addr = NULL;
// 		club->tex[i].bpp = 0;
// 		club->tex[i].line_len = 0;
// 		club->tex[i].endian = 0;
// 		club->tex[i].width = 0;
// 		club->tex[i].height = 0;
// 		club->tex[i].path = NULL;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < SPRITE_TYPES)
// 	{
// 		club->sprite_textures[i].img = NULL;
// 		club->sprite_textures[i].addr = NULL;
// 		club->sprite_textures[i].bpp = 0;
// 		club->sprite_textures[i].line_len = 0;
// 		club->sprite_textures[i].endian = 0;
// 		club->sprite_textures[i].width = 0;
// 		club->sprite_textures[i].height = 0;
// 		i++;
// 	}
// }

void	init_club_defaults(t_club *club)
{
	init_ptrs_defaults(club);
	init_values_defaults(club);
	init_door_tex_defaults(club);
	init_tex_arrays_defaults(club);
}
