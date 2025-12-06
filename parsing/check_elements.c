#include "../include/cub3d.h"

static bool	is_empty(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

static bool	is_texture_key(char *line)
{
	if (!line)
		return (false);
	while (*line == ' ')
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
	while (*line == ' ')
		line++;
	if (*line == 'F' || *(line + 1) == 'C')
		return (true);
	return (false);
}

static int	check_elements(t_club *club, char **lines)
{
	int	i;
	int	ret;

	i = 0;
	while (lines[i])
	{
		if (is_empty(lines[i]))
			i++;
		else if (is_texture_key(lines[i]))
		{
			res = prase_texture(lines[i], club);
			if (res == -1)
				return (-1);
		}
		else if (is_clor_key(lines[i]))
		{
			res = parse_color(lines[i], club);
			if (res == -1)
				return (-1);
		}
		else
			break ;
		i++;
	}
	return (i);
}