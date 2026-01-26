/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:30:01 by hguo              #+#    #+#             */
/*   Updated: 2026/01/26 17:06:18 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** Flood fill used to verify that the map is closed.
** Returns false if out of bounds or reaching a space (' ').
** Returns true for walls ('1') or visited cells ('v').
** Marks floor cells as 'v' and checks all 4 directions.
*/
// static bool	flood_fill_check(t_club *club, char **map, int x, int y)
// {
// 	if (y < 0 || y >= club->map.height || x < 0 || x >= club->map.width)
// 		return (false);
// 	if (map[y][x] == ' ')
// 		return (false);
// 	if (map[y][x] == '1' || map[y][x] == 'v')
// 		return (true);
// 	map[y][x] = 'v';
// 	if (!flood_fill_check(club, map, x, y - 1))
// 		return (false);
// 	if (!flood_fill_check(club, map, x, y + 1))
// 		return (false);
// 	if (!flood_fill_check(club, map, x - 1, y))
// 		return (false);
// 	if (!flood_fill_check(club, map, x + 1, y))
// 		return (false);
// 	return (true);
// }

static bool	is_surrounded_by_zero(char **map, int x, int y)
{
	if (map[y - 1][x] == '0' || map[y + 1][x] == '0' \
		|| map[y][x - 1] == '0' || map[y][x + 1] == '0')
		return (true);
	return (false);
}

static bool	find_player_position(t_club *club)
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
					return (err_msg("Error: Player incorrectly placed."), \
						false);
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

static bool	init_player_direction(t_club *club)
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

static bool	is_cell_closed(char **map, int x, int y)
{
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' \
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (false);
	return (true);
}

static bool	check_map_closed(t_club *club)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (club->map.grid[y])
	{
		x = 0;
		while (club->map.grid[y][x])
		{
			c = club->map.grid[y][x];
			if (c == '0' || c == 'N' || c == 'S'
				|| c == 'E' || c == 'W')
			{
				if (!is_cell_closed(club->map.grid, x, y))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	prepare_map(t_club *club)
{
	char	**map_copy;

	if (!club || !club->map.grid)
		return (false);
	if (!pad_map(club))
		return (false);
	map_copy = copy_map(club);
	if (!map_copy)
		return (false);
	if (!find_player_position(club) || !init_player_direction(club))
		return (free_array(map_copy), false);
	if (!check_map_closed(club))
	{
		err_msg("ERROR: map is not surrounded by walls");
		return (free_array(map_copy), false);
	}
	free_array(map_copy);
	return (true);
}
