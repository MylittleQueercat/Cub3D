#include "../include/cub3d.h"

static bool	fill_door_array(t_club *club)
{
	int	y;
	int	x;
	int	idx;

	y = 0;
	idx = 0;
	while (club->map.grid[y] && idx < club->door_count)
	{
		x = 0;
		while (club->map.grid[y][x] && idx < club->door_count)
		{
			if (club->map.grid[y][x] == 'D')
			{
				club->doors[idx].x = x + 0.5;
				club->doors[idx].y = y + 0.5;
				club->doors[idx].is_open = false;
				idx++;
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	init_doors(t_club *club)
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

/*
** try_open_door:
** Checks the map cell directly in front of the player.
** If it contains a closed door ('D'), mark it as open and update the map to '0'
** so the player can walk through.
*/
void	try_open_door(t_club *club)
{
	int	i;
	int	check_x;
	int	check_y;

	if (!club || !club->doors || !club->map.grid)
		return ;
	check_x = (int)(club->player.x + club->player.dir_x);
	check_y = (int)(club->player.y + club->player.dir_y);
	i = 0;
	while (i < club->door_count)
	{
		if ((int)(club->doors[i].x) == check_x \
			&& (int)(club->doors[i].y) == check_y \
			&& club->doors[i].is_open == false)
		{
			club->doors[i].is_open = true;
			club->map.grid[check_y][check_x] = '0';
			return ;
		}
		i++;
	}
}
