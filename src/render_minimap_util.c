#include "../include/cub3d.h"

int	mm_color_for_cell(char c)
{
	if (c == '1')
		return (MM_WALL);
	if (c == 'D')
		return (MM_DOOR);
	return (MM_BG);
}

void	mm_draw_square(t_img *img, int x, int y, int size, int color)
{
	int	sx;
	int	sy;

	sy = 0;
	while (sy < size)
	{
		sx = 0;
		while (sx < size)
		{
			put_pixel(img, x + sx, y + sy, color);
			sx++;
		}
		sy++;
	}
}

void	mm_draw_player_pony(t_img *img, int cx, int cy, int tile)
{
	int	radius;
	int	r2;
	int	x;
	int	y;

	radius = tile / 3;
	if (radius < 3)
		radius = 3;
	r2 = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= r2)
				put_pixel(img, cx + x, cy + y, MM_PLAYER);
			x++;
		}
		y++;
	}
}

void	mm_draw_sprite(t_img *img, int cx, int cy, int tile)
{
	int	radius;
	int	r2;
	int	x;
	int	y;

	radius = tile / 4;
	if (radius < 2)
		radius = 2;
	r2 = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= r2)
				put_pixel(img, cx + x, cy + y, MM_SPRITE);
			x++;
		}
		y++;
	}
}

