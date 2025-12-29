#include "../include/cub3d.h"

int	count_char_in_map(char **map, char target)
{
	int	count;
	int	x;
	int	y;

	if (!map)
		return (0);
	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == target)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

// static bool	fill_sprite_array(t_club *club)
// {
// 	int	y;
// 	int	x;
// 	int	idx;

// 	y = 0;
// 	idx = 0;
// 	while (club->map.grid[y] && idx < club->sprite_count)
// 	{
// 		x = 0;
// 		while (club->map.grid[y][x] && idx < club->sprite_count)
// 		{
// 			if (club->map.grid[y][x] == '2')
// 			{
// 				club->sprites[idx].x = x + 0.5;
// 				club->sprites[idx].y = y + 0.5;
// 				club->sprites[idx].radius = 0.40;
// 				club->sprites[idx].visible = false;
// 				club->sprites[idx].distance = 0;
// 				club->sprites[idx].phase = (y * 7 + x * 13) * 0.37;
// 				club->sprites[idx].found = false;
// 				//club->sprites[idx].img = NULL;
// 				idx++;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (true);
// }

bool	init_sprits(t_club *club)
{
	if (!club || !club->map.grid)
		return (false);
	club->sprite_count = count_sprites_all(club->map.grid);
	if (club->sprite_count == 0)
	{
		club->sprites = NULL;
		return (false);
	}
	// club->sprites = malloc(sizeof(t_sprite) * club->sprite_count);
	club->sprites = ft_calloc(club->sprite_count, sizeof(t_sprite));
	if (!club->sprites)
		return (false);
	if (!fill_sprite_array(club))
	{
		free(club->sprites);
		club->sprites = NULL;
		club->sprite_count = 0;
		return (false);
	}
	return (true);
}

static int	load_sprite_texture(t_club *club, t_img *tex, const char *path)
{
	if (!club || !tex || !path)
		return (1);
	if (!is_valid_xpm_file((char *)path))
		return (err_msg("Error: sprite XPM missing"), 1);
	if (tex->img)
		mlx_destroy_image(club->mlx, tex->img);
	tex->img = mlx_xpm_file_to_image(club->mlx, (char *)path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (err_msg("Error: failed to load sprite texture"), 1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (err_msg("Error: failed to get sprite image addr"), 1);
	return (0);
}

int	load_sprites(t_club *club)
{
	if (!club)
		return (1);
	if (load_sprite_texture(club, &club->sprite_textures[SPR_PONY],
			"xpms/pony_64.xpm"))
		return (1);
	if (load_sprite_texture(club, &club->sprite_textures[SPR_SPARKLE],
			"xpms/pikachu_64.xpm"))
		return (1);
	if (load_sprite_texture(club, &club->sprite_textures[SPR_HEART],
			"xpms/neox_64.xpm"))
		return (1);
	if (load_sprite_texture(club, &club->sprite_textures[SPR_DISCO],
			"xpms/cpr_64.xpm"))
		return (1);
	return (0);
}
