#include "../include/cub3d.h"

// static char **grow_array(char **arr, int old_size, int new_size)
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

// static int	add_line(char **arr, int *count, int *size, char *line)
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

// static int	get_line_count(const char *file)
// {
// 	int		count;
// 	int		fd;
// 	char	*line;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (-1);
// 	count = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		count++;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (count);
// }

// char	**read_file(const char *file)
// {
// 	char	**res;
// 	char	*line;
// 	int		i;
// 	int		fd;
// 	int		map_lines;

// 	map_lines = get_line_count(file);
// 	if (map_lines <= 0)
// 		return (NULL);
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	res = malloc(sizeof(char *) * (map_lines + 1));
// 	if (!res)
// 	{
// 		close(fd);
// 		return (NULL);
// 	}
// 	i = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		res[i++] = line;
// 		line = get_next_line(fd);
// 	}
// 	res[i] = NULL;
// 	close(fd);
// 	return (res);
// }

static int	count_lines(const char *file)
{
	int		fd;
	int		count;
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

static char	**load_lines(const char *file, int size)
{
	char	**res;
	char	*line;
	int		fd;
	int		i;

	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free(res), NULL);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		res[i] = line;
		i++;
		line = get_next_line(fd);
	}
	res[i] = NULL;
	close(fd);
	return (res);
}

char	**read_file(const char *file)
{
	int		size;
	char	**res;

	size = count_lines(file);
	if (size < 0)
		return (NULL);
	res = load_lines(file, size);
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

static int	check_elements_complete(t_club *club)
{
	if (!club->tex[TEX_NO].path || !club->tex[TEX_SO].path \
		|| !club->tex[TEX_WE].path || !club->tex[TEX_EA].path)
		return (err_msg("Error: Missing texture(s)"), -1);
	if (club->floor_color == -1 || club->ceiling_color == -1)
		return (err_msg("Error: Missing color(s)"), -1);
	return (0);
}

int	parsing(t_club *club, char **file)
{
	if (!file || !*file)
		return (err_msg("Error: No file content provided"), -1);
	if (get_map(club, file) == -1)
		return (err_msg("Error: Map missing"), -1);
	if (!is_map_at_the_end(club, file))
		return (err_msg("Error: Map is not at the end of the file"), -1);
	if (!check_map_valid(club))
		return (free_array(club->map.grid), -1);
	if (check_elements(club, file) == -1)
		return (free_array(club->map.grid), -1);
	if (check_elements_complete(club) == -1)
		return (free_array(club->map.grid), -1);
	if (parse_map(club) == -1)
		return (free_array(club->map.grid), -1);
	return (0);
}
