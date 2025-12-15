#include "../include/cub3d.h"

int	count_char_in_map(char **map, char target)
{
	int	count;
	int	x;
	int	y;

	if (!map)
		return (0);
	for (int k = 0; map[k]; k++)
		printf("%s", map[k]);
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

static bool	fill_sprite_array(t_club *club)
{
	int	y;
	int	x;
	int	idx;

	y = 0;
	idx = 0;
	while (club->map.grid[y] && idx < club->sprite_count)
	{
		x = 0;
		while (club->map.grid[y][x] && idx < club->sprite_count)
		{
			if (club->map.grid[y][x] == '2')
			{
				club->sprites[idx].x = x + 0.5;
				club->sprites[idx].y = y + 0.5;
				club->sprites[idx].visible = false;
				club->sprites[idx].distance = 0;
				//club->sprites[idx].img = NULL;
				idx++;
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	init_sprits(t_club *club)
{
	if (!club || !club->map.grid)
		return (false);
	club->sprite_count = count_char_in_map(club->map.grid, '2');
	if (club->sprite_count == 0)
		return (false);
	club->sprites = malloc(sizeof(t_sprite) * club->sprite_count);
	if (!club->sprites)
		return (false);
	return (fill_sprite_array(club));
}

int	load_sprites(t_club *club)
{
	if (!club || !club->sprites)
		return (1);
	club->sprite_texture.img = mlx_xpm_file_to_image(club->mlx, \
		"xpms/pony.xpm", &club->sprite_texture.width, \
		&club->sprite_texture.height);
	if (!club->sprite_texture.img)
		return (1);
	return (0);
}
