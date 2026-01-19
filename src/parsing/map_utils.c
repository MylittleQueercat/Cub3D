#include "../include/cub3d.h"

bool	is_valid_char(char c, bool bonus)
{
	if (c == '0' || c == '1' || c == ' ' || c == '\n'\
		|| c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (true);
	if (bonus && ((c >= '2' && c <= '5') || c == 'D'))
		return (true);
	return (false);
}

bool	check_valid_chars(t_club *club)
{
	int	y;
	int	x;

	y = 0;
	while (y < club->map.height)
	{
		x = 0;
		while (club->map.grid[y][x] != '\0')
		{
			if (!is_valid_char(club->map.grid[y][x], true))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_player_count(t_club *club)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (club->map.grid[y])
	{
		x = 0;
		while (club->map.grid[y][x])
		{
			if (club->map.grid[y][x] == 'N' || club->map.grid[y][x] == 'S' \
				|| club->map.grid[y][x] == 'E' || club->map.grid[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (false);
	return (true);
}

bool	check_first_last_row(t_club *club)
{
	int	x;
	int	last_y;

	if (!club->map.height)
		return (false);
	last_y = club->map.height - 1;
	x = 0;
	while (club->map.grid[0][x])
	{
		if (club->map.grid[0][x] != '1' \
			&& !ft_is_whitespace(club->map.grid[0][x]))
			return (false);
		x++;
	}
	x = 0;
	while (club->map.grid[last_y][x])
	{
		if (club->map.grid[last_y][x] != '1' \
			&& !ft_is_whitespace(club->map.grid[last_y][x]))
			return (false);
		x++;
	}
	return (true);
}
