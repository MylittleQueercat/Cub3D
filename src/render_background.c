#include "../include/cub3d.h"

void	render_background(t_club *club)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			color = club->ceiling_color;
		else
			color = club->floor_color;
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(&club->img, x, y, color);
			x++;
		}
		y++;
	}
}