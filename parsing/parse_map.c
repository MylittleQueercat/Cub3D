#include "../include/cub3d.h"

static bool	is_valid_char(char c, bool bonus)
{
	if (c == '0' || c == '1' || c == ' ')
		return (true);
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (true);
	if (bonus && (c == 2 || c == 'D'))
		return (true);
	return (false);
}

static bool	check_valid_chars(t_club *club)
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

static bool	check_player_count(t_club *club)
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

static bool	check_first_last_row(t_club *club)
{
	int	x;
	int last_y;

	if (!club->map.height)
		return (false);
	last_y = club->map.height - 1;
	x = 0;
	while (club->map.grid[0][x])
	{
		if (club->map.grid[0][x] != '1' && club->map.grid[0][x] != ' ')
			return (false);
		x++;
	}
	x = 0;
	while (club->map.grid[last_y][x])
	{
		if (club->map.grid[last_y][x] != '1' && club->map.grid[last_y][x] != ' ')
			return (false);
		x++;
	}
	return (true);
}

static bool	check_sides(t_club *club)
{
	int	i;
	int	len;

	i = 0;
	while (club->map.grid[i])
	{
		len = ft_strlen(club->map.grid[i]);
		if (len == 0)
			return (false);
		if (club->map.grid[i][0] != '1' && club->map.grid[i][0] != ' ')
			return (false);
		if (club->map.grid[i][len - 1] != '1' && club->map.grid[i][len - 1] != ' ')
			return (false);
		i++;
	}
	return (true);
}

int parse_map(t_club *club, char **file)
{
	if (!get_map(club, file))
		return (-1);
	if (!check_valid_chars(club) || !check_player_count(club) \
		|| !check_first_last_row(club) || !check_sides(club))
		return (-1);
	return (0);
}
