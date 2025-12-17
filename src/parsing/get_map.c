#include "../include/cub3d.h"

bool	is_valid_map_line(char *line)
{
	int	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
		|| line[i] == '\v' || line[i] == '\f')
		i++;
	if (line[i] == '\0')
		return (false);
	if (line[i] == '1')
		return (true);
	return (false);
}

// static bool	is_empty_map(char **line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (is_valid_map_line(line[i]))
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

static int count_map_lines(char **file)
{
	int	i;
	int len;

	if (!file)
		return (0);
	i = 0;
	len = 0;
	while (file[i])
	{
		if (is_valid_map_line(file[i]))
			len++;
		i++;
	}
	return (len);
}

static void	set_map_size(t_club *club)
{
	int	i;
	int len;

	i = 0;
	club->map.height = 0;
	club->map.width = 0;
	while (club->map.grid[i])
	{
		len = ft_strlen(club->map.grid[i]);
		if (len > club->map.width)
			club->map.width = len;
		club->map.height++;
		i++;
	}
}

int	get_map(t_club *club, char **file)
{
	int i;
	int j;

	if (!file || !*file)
		return (-1);
	i = 0;
	while (file[i] && !is_valid_map_line(file[i]))
		i++;
	if (!file[i])	
		return (-1);
	club->map.grid = malloc(sizeof(char *) * (count_map_lines(file) + 1));
	if (!club->map.grid)
		return (-1);
	j = 0;
	while (file[i] && is_valid_map_line(file[i]))
	{
		club->map.grid[j] = ft_strdup(file[i]);
		if (!club->map.grid[j])
			return (free_array(club->map.grid), -1);
		j++;
		i++;
	}
	club->map.grid[j] = NULL;
	set_map_size(club);
	club->map.map_end_index = i;
	// for (int k = 0; club->map.grid[k]; k++)
	// 	printf("%s", club->map.grid[k]);
	return (0);
}
 