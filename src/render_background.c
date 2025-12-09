#include "../include/cub3d.h"

static int	get_tex_color(t_tex *tex, int tx, int ty)
{
	char	*pixel;

	if (!tex->img || !tex->addr)
		return (0);
	if (tx < 0 || tx >= tex->width || ty < 0 || ty >= tex->height)
		return (0);
	pixel = tex->addr + ty * tex->line_len + tx * (tex->bpp / 8);
	return (*(unsigned int *)pixel);
}

void	render_background(t_club *club)
{
	int		x;
	int		y;
	int		tx;
	int		ty;
	int		color;
	t_tex	*tex;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < HEIGHT / 2)
			tex = &club->tex[TEX_CEIL];
		else
			tex = &club->tex[TEX_FLOOR];
		// 没纹理就用原来的纯色
		if (!tex->img || !tex->addr)
		{
			int	fallback = (y < HEIGHT / 2)
				? club->ceiling_color : club->floor_color;
			x = 0;
			while (x < WIDTH)
				put_pixel(&club->img, x++, y, fallback);
			y++;
			continue ;
		}

		x = 0;
		while (x < WIDTH)
		{
			// 平铺
			tx = x % tex->width;
			if (y < HEIGHT / 2)
				ty = y % tex->height;              // 天花板
			else
				ty = (y - HEIGHT / 2) % tex->height; // 地板

			color = get_tex_color(tex, tx, ty);
			put_pixel(&club->img, x, y, color);
			x++;
		}
		y++;
	}
}

