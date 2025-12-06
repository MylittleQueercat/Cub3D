#include "../include/cub3d.h"

int	count_sprites(char **map)
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
			if (map[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

bool	find_sprite_position(t_club *club)
{
	int	y;
	int	x;
	int	idx;

	if (!club || !club->map.grid)
		return (false);
	y = 0;
	idx = 0;
	club->sprite_count = count_sprites(club->map.grid);
	if (club->sprite_count == 0)
		return (false);
	club->sprites = malloc(sizeof(t_sprite) * club->sprite_count);
	if (!club->sprites)
		return (false);
	while (club->map.grid[y])
	{
		x = 0;
		while (club->map.grid[y][x])
		{
			if (club->map.grid[y][x] == '2')
			{
				club->sprites[idx].x = x;
				club->sprites[idx].y = y;
				club->sprites[idx].texture = "sprite.xpm";  // 以后再替换成实际贴图
				idx++;
			}
			x++;
		}
		y++;
	}
	return (true);
}

int	count_doors(char **map)
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
			if (map[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

bool	find_door_position(t_club *club)
{
	int	y;
	int	x;
	int	idx;

	if (!club || !club->map.grid)
		return (false);
	y = 0;
	idx = 0;
	club->door_count = count_doors(club->map.grid);
	if (club->door_count == 0)
		return (false);
	club->doors = malloc(sizeof(t_door) * club->door_count);
	if (!club->doors)
		return (false);
	while (club->map.grid[y])
	{
		x = 0;
		while (club->map.grid[y][x])
		{
			if (club->map.grid[y][x] == 'D')
			{
				club->doors[idx].x = x;
				club->doors[idx].y = y;
				club->doors[idx].is_open = false;
				idx++;
			}
			x++;
		}
		y++;
	}
	return (true);
}
