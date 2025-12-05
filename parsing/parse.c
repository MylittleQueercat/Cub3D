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

