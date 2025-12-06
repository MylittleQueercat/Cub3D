#include "../include/cub3d.h"

char **read_file(const char *file)
{
	char	**res;
	char	*line;
	int		size;
	int		count;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	size = INITIAL_CAP;
	res = malloc(sizeof(char *) * size);
	if (!res)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (count >= size)
		{
			size *= 2;
			res = realloc(res, sizeof(char *) * size);
			if (!res)
				return (free(line), NULL);
		}
		res[count++] = line;
		line = get_next_line(fd);
	}
	res[count] = NULL;
	close(fd);
	return (res);
}

bool	is_cub_file(char *arg)
{
	int	len;
	int	fd;

	if	(!arg)
		return (false);
	len = ft_strlen(arg);
	if (len < 4 || ft_strcmp(arg + len - 4, ".cub") != 0)
		return (false);
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

int	parsing(t_club *club, char **file)
{
	int	start_line;

	start_line = check_elements(club, file);
	if (!start_line)
		return (-1);
	if (!parse_map(club, file + start_line))
		return (-1);
	return (0);
}