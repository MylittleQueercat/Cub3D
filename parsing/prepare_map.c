#include "../include/cub3d.h"

char **copy_map(t_club *club)
{
	char **map;
	int	i;

	map = malloc(sizeof(char *) * (club->map.height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < club->map.height)
	{
		map[i] = ft_strdup(club->map.grid[i]);
		if (!map[i])
			return (free_array(map), NULL);
		i++;
	}
	map[i] = NULL;
	return (map);
}

/*
** Flood fill used to verify that the map is closed.
** Returns false if out of bounds or reaching a space (' ').
** Returns true for walls ('1') or visited cells ('v').
** Marks floor cells as 'v' and checks all 4 directions.
*/
bool	flood_fill_check(char **map, int x, int y, int height, int width)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (false);
	if (map[y][x] == ' ')
		return (true);
	if (map[y][x] == '1' || map[y][x] == 'v')
		return (true);
	map[y][x] = 'v';
	if (!flood_fill_check(map, x, y -1, height, width))
		return (false);
	if (!flood_fill_check(map, x, y + 1, height, width))
		return (false);
	if (!flood_fill_check(map, x -1, y, height, width))
		return (false);
	if (!flood_fill_check(map, x + 1, y, height, width))
		return (false);
	return (true);
}

static bool	is_surrounded_by_zero(char **map, int x, int y)
{
	if (map[y - 1][x] == '0' || map[y + 1][x] == '0' \
		|| map[y][x - 1] == '0' || map[y][x + 1] == '0')
		return (true);
	return (false);
}

bool	find_player_position(t_club *club)
{
	int	y;
	int	x;

	y = 0;
	while (club->map.grid[y])
	{
		x = 0;
		while (club->map.grid[y][x])
		{
			if (club->map.grid[y][x] == 'N' || club->map.grid[y][x] == 'S'
				|| club->map.grid[y][x] == 'W' || club->map.grid[y][x] == 'E')
			{
				if (!is_surrounded_by_zero(club->map.grid, x, y))
					return (false);
				club->player.pos = club->map.grid[y][x];
				club->player.x = x + 0.5;
				club->player.y = y + 0.5;
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

bool	init_player_direction(t_club *club)
{
	if (club->player.pos == 'N')
	{
		club->player.dir_x = 0;
		club->player.dir_y = -1;
	}
	else if (club->player.pos == 'S')
	{
		club->player.dir_x = 0;
		club->player.dir_y = 1;
	}
	else if (club->player.pos == 'W')
	{
		club->player.dir_x = -1;
		club->player.dir_y = 0;
	}
	else if (club->player.pos == 'E')
	{
		club->player.dir_x = 1;
		club->player.dir_y = 0;
	}
	else
		return (false);
	club->player.plane_x = -club->player.dir_y * FOV;
	club->player.plane_y = club->player.dir_x * FOV;
	return (true);
}

bool	prepare_map(t_club *club)
{
	char	**map_copy;

	map_copy = copy_map(club);
	if (!map_copy)
		return (false);
	if (!find_player_position(club) || !init_player_direction(club))
		return (free_array(map_copy), false);
	if (!flood_fill_check(map_copy, (int)club->player.x, \
		(int)club->player.y, club->map.height, club->map.width))
		return (free_array(map_copy), false);
	free_array(map_copy);
	return (true);
}