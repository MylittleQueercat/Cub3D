#include "../include/cub3d.h"

// char **grow_array(char **arr, int old_size, int new_size)
// {
// 	char	**new_arr;
// 	int		i;

// 	tmp = malloc(sizeof(char *) * (new_size));
// 	if (!new_arr)
// 		return (NULL);
// 	i = 0;
// 	while (i < old_size)
// 	{
// 		new_arr[i] = arr[i];
// 		i++;
// 	}
// 	free(arr);
// 	return (new_arr);
// }

// int	add_line(char **arr, int *count, int *size, char *line)
// {
// 	char **tmp;

// 	if (*count >= *size)
// 	{
// 		tmp = grow_array(*arr, *count, (*size) * 2);
// 		if (!tmp)
// 			return (-1);
// 		*arr = tmp;
// 		*size = (*size) * 2;
// 	}
// 	(*arr)[*count] = line;
// 	*count += 1;
// 	return (0);
// }

// char **read_file(const char *file)
// {
// 	char	**res;
// 	char	*line;
// 	int		size;
// 	int		count;
// 	int		fd;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	size = INITIAL_CAP;
// 	count = 0;
// 	res = malloc(sizeof(char *) * size);
// 	if (!res)
// 	{
// 		close(fd);
// 		return (NULL);
// 	}
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (add_line(&res, &count, &size, line) == -1)
// 			return (free_array(res), NULL);
// 		line = get_next_line(fd);
// 	}
// 	res[count] = NULL;
// 	close(fd);
// 	return (res);
// }

static int	get_line_count(const char *file)
{
	int		count;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**read_file(const char *file)
{
	char	**res;
	char	*line;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	res = malloc(sizeof(char *) * (get_line_count(file) + 1));
	if (!res)
	{
		close(fd);
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		res[i++] = line;
		line = get_next_line(fd);
	}
	res[i] = NULL;
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

	if (!file && !*file)
		return (-1);
	start_line = check_elements(club, file);
	if (!start_line)
		return (-1);
	if (!parse_map(club, file + start_line))
		return (-1);
	return (0);
}
