#include "../include/cub3d.h"

static bool is_all_number(char *s)
{
	int	i;

	if (!s || s[0] == '\0')
		return (false);
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	validate_color_values(char **nums, int *r, int *g, int *b)
{
	if (!nums || !nums[0] || !nums[1] || !nums[2] || nums[3])
		return (-1);
	if (!is_all_number(nums[0]) || !is_all_number(nums[1]) \
			|| !is_all_number(nums[2]))
		return (-1);
	*r = ft_atoi(nums[0]);
	*g = ft_atoi(nums[1]);
	*b = ft_atoi(nums[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (-1);
	return (0);
}
int parse_color(char *line, t_club *club)
{
	char **nums;
	int	r;
	int	g;
	int	b;

	while (*line == ' ')
		line++;
	if (*line != 'F' && *line != 'C')
		return (-1);
	line++;
	while (*line == ' ')
		line++;
	nums = ft_split(line, ',');
	if (validate_color_values(nums, &r, &g, &b) < 0)
		return (free_array(nums), -1);
	if (*(line - 1) == 'F')
		club->floor_color = (r << 16) | (g << 8) | b;
	else
		club->ceiling_color = (r << 16) | (g << 8) | b;
	return (0);
}
