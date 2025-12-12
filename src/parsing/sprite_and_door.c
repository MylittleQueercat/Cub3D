#include "../include/cub3d.h"

static int	count_char_in_map(char **map, char target)
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

static bool	is_valid_tile(char tile)
{
	return (tile == '0' || tile == '2' || tile == 'D');
}

static bool	validate_position(t_club *club, int x, int y)
{
	if (y == 0 || y == club->map.height - 1 \
		|| x == 0 || x == club->map.width - 1)
		return (false);
	if (x == club->player.x && y == club->player.y)
		return (false);
	if (!is_valid_tile(club->map.grid[y][x]))
		return (false);
	return (true);
}

static bool	fill_sprite_array(t_club *club)
{
	int	y;
	int	x;
	int	idx;

	y = 0;
	idx = 0;
	while (club->map.grid[y])
	{
		x = 0;
		while (club->map.grid[y][x])
		{
			if (club->map.grid[y][x] == '2' && validate_position(club, x, y))
			{
				club->sprites[idx].x = x;
				club->sprites[idx].y = y;
				club->sprites[idx].visible = false;
				club->sprites[idx].distance = 0;
				club->sprites[idx].texture = "sprite.xpm";  // 以后再替换成实际贴图
				idx++;
			}
			x++;
		}
		y++;
	}
	return (true);
}

static bool	fill_door_array(t_club *club)
{
	int	y;
	int	x;
	int	idx;

	y = 0;
	idx = 0;
	while (club->map.grid[y])
	{
		x = 0;
		while (club->map.grid[y][x])
		{
			if (club->map.grid[y][x] == 'D' && validate_position(club, x, y))
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

bool	find_sprite_position(t_club *club)
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

bool	find_door_position(t_club *club)
{
	if (!club || !club->map.grid)
		return (false);
	club->door_count = count_char_in_map(club->map.grid, 'D');
	if (club->door_count == 0)
		return (false);
	club->doors = malloc(sizeof(t_door) * club->door_count);
	if (!club->doors)
		return (false);
	return (fill_door_array(club));
}
