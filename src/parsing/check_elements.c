#include "../include/cub3d.h"

static bool	is_empty(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (!ft_is_whitespace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_texture_key(char *line)
{
	if (!line)
		return (false);
	while (ft_is_whitespace(*line))
		line++;
	if (*line == 'N' && *(line + 1) == 'O')
		return (true);
	if (*line == 'S' && *(line + 1) == 'O')
		return (true);
	if (*line == 'W' && *(line + 1) == 'E')
		return (true);
	if (*line == 'E' && *(line + 1) == 'A')
		return (true);
	return (false);
}

static bool	is_color_key(char *line)
{
	if (!line)
		return (false);
	while (ft_is_whitespace(*line))
		line++;
	if (*line == 'F' || *line == 'C')
		return (true);
	return (false);
}

int	check_elements(t_club *club, char **lines)
{
	int	i;
	int	ret;

	i = 0;
	while (lines[i])
	{
		if (is_empty(lines[i]))
			;
		else if (is_texture_key(lines[i]))
		{
			ret = parse_texture(lines[i], club);
			if (ret == -1)
				return (err_msg("parse texture fails"), -1);
		}
		else if (is_color_key(lines[i]))
		{
			ret = parse_color(lines[i], club);
			if (ret == -1)
				return (err_msg("parse color fails"), -1);
		}
		else
			break ;
		i++;
	}
	if (club->floor_color == -1 || club->ceiling_color == -1)
		return (err_msg("Error: Missing colors"), -1);
	return (i);
}
