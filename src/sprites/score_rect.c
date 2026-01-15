#include "../include/cub3d.h"

void	ui_draw_rect(t_img *img, t_rect r, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < r.h)
	{
		i = 0;
		while (i < r.w)
		{
			put_pixel(img, r.x + i, r.y + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_hline(t_img *img, int x, int y, int w, int color)
{
	int	i;

	i = 0;
	while (i < w)
	{
		put_pixel(img, x + i, y, color);
		i++;
	}
}

static void	draw_vline(t_img *img, int x, int y, int h, int color)
{
	int	i;

	i = 0;
	while (i < h)
	{
		put_pixel(img, x, y + i, color);
		i++;
	}
}

void	ui_draw_border(t_img *img, t_rect r, int color, int t)
{
	int	k;

	k = 0;
	while (k < t)
	{
		draw_hline(img, r.x, r.y + k, r.w, color);
		draw_hline(img, r.x, r.y + r.h - 1 - k, r.w, color);
		draw_vline(img, r.x + k, r.y, r.h, color);
		draw_vline(img, r.x + r.w - 1 - k, r.y, r.h, color);
		k++;
	}
}
