#include "../include/cub3d.h"

static bool	is_valid_char(char c, bool bonus)
{
	if (c == '0' || c == '1' || c == ' ' || c == '\n'\
		|| c == 'N' || c == 'W' || c == 'E' || c == 'S')
		return (true);
	if (bonus && ((c >= '2' && c <= '5') || c == 'D'))
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
		if (club->map.grid[0][x] != '1' && !ft_is_whitespace(club->map.grid[0][x]))
			return (false);
		x++;
	}
	x = 0;
	while (club->map.grid[last_y][x])
	{
		if (club->map.grid[last_y][x] != '1' && !ft_is_whitespace(club->map.grid[last_y][x]))
			return (false);
		x++;
	}
	return (true);
}

static char	*pad_line(char *line, int new_len)
{
	int		i;
	int		old_len;
	char	*new_line;

	old_len = ft_strlen(line);
	new_line = malloc(new_len + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < old_len)
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < new_len)
		new_line[i++] = ' ';
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

static bool	check_sides(t_club *club)
{
	int	i;

	i = 0;
	while (club->map.grid[i])
	{
		if (ft_strlen(club->map.grid[i]) == 0)
			return (false);
		club->map.grid[i] = pad_line(club->map.grid[i], club->map.width);
		if (!club->map.grid[i])
			return (false);
		if (club->map.grid[i][0] != '1' && club->map.grid[i][0] != ' ')
			return (false);
		if (club->map.grid[i][club->map.width - 1] != '1' \
			&& !ft_is_whitespace(club->map.grid[i][club->map.width - 1]))
			return (false);
		i++;
	}
	return (true);
}

static bool	check_map_size(t_club *club)
{
	int	y;

	if (club->map.height < 3 || club->map.width < 3)
		return (false);
	y = 0;
	while (club->map.grid[y])
	{
		// if (!ft_strchr(club->map.grid[y], '0') && !ft_strchr(club->map.grid[y], '1') \
		// 	&& !ft_strchr(club->map.grid[y], 'N') && !ft_strchr(club->map.grid[y], 'S')  \
		// 	&& !ft_strchr(club->map.grid[y], 'W') && !ft_strchr(club->map.grid[y], 'E'))
		// 	return (false);
		if (!ft_strchr(club->map.grid[y], '0') && !ft_strchr(club->map.grid[y], '1') \
			&& !ft_strchr(club->map.grid[y], 'N') && !ft_strchr(club->map.grid[y], 'S') \
			&& !ft_strchr(club->map.grid[y], 'W') && !ft_strchr(club->map.grid[y], 'E') \
			&& !ft_strchr(club->map.grid[y], '2') && !ft_strchr(club->map.grid[y], '3') \
			&& !ft_strchr(club->map.grid[y], '4') && !ft_strchr(club->map.grid[y], '5') \
			&& !ft_strchr(club->map.grid[y], 'D'))
			return (false);
		y++;
	}
	return (true);
}

// static bool	is_map_at_the_end(t_club *club)
// {
// 	int	i;
// 	int	j;

// 	if (!club->map.grid)
// 		return (false);
// 	i = 0;
// 	while (club->map.grid[i])
// 		i++;
// 	if (i == 0)
// 		return (false);
// 	i--;
// 	j = 0;
// 	while (club->map.grid[i][j])
// 	{
// 		if (!ft_is_whitespace(club->map.grid[i][j]))
// 			return (false);
// 		j++;
// 	}
// 	return (true);
// }

bool	is_map_at_the_end(t_club *club, char **file)
{
	int	i;

	if (!file || !club->map.grid)
		return (false);
	i = club->map.map_end_index;
	while (file[i])
	{
		if (!is_empty_line(file[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_map_valid(t_club *club)
{
	if (!club->map.grid)
		return (err_msg("Error: map missing"), false);
	// if (!is_map_at_the_end(club))
	// 	return (err_msg("Error: map is not at the end of the file"), false);
	if (!check_valid_chars(club))
		return (err_msg("Error: map has invalid character"), false);
	if (!check_first_last_row(club) || !check_sides(club))
		return (err_msg("Error: map is not surrounded by walls"), false);
	if (!check_map_size(club))
		return (err_msg("Error: map size is not right"), false);
	if (!check_player_count(club))
		return (err_msg("Error: map should have one and only one player"), false);
	return (true);
}
