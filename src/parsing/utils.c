#include "../include/cub3d.h"

bool	is_empty_line(char *line)
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
