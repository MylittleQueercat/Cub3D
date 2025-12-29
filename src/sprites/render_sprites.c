#include "../include/cub3d.h"

static void	calc_sprite_info(t_club *club, t_sprite *s)
{
	double	dx;
	double	dy;
	double	inv_det;
	double	ty;

	dx = s->x - club->player.x;
	dy = s->y - club->player.y;
	s->distance = dx * dx + dy * dy;

	inv_det = 1.0 / (club->player.plane_x * club->player.dir_y
			- club->player.dir_x * club->player.plane_y);
	s->transform_x = inv_det * (club->player.dir_y * dx - club->player.dir_x * dy);
	s->transform_y = inv_det * (-club->player.plane_y * dx + club->player.plane_x * dy);
	if (s->transform_y <= 0.0001)
	{
		s->visible = false;
		return ;
	}
	s->visible = true;
	ty = s->transform_y;
	if (ty < 0.35)
		ty = 0.35;
	s->screen_x = (int)((WIDTH / 2) * (1 + s->transform_x / ty));
	s->height = abs((int)((HEIGHT / ty) * 0.8));
	if (s->height > (int)(HEIGHT * 0.90))
		s->height = (int)(HEIGHT * 0.90);

	s->width = s->height;
}


static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sort_sprites(t_club *club)
{
	int	i;
	int	j;

	i = 0;
	while (i < club->sprite_count)
	{
		j = i + 1;
		while (j < club->sprite_count)
		{
			if (club->sprites[i].distance < club->sprites[j].distance)
				swap_sprites(&club->sprites[i], &club->sprites[j]);
			j++;
		}
		i++;
	}
}


static void	draw_sprite_pixel(t_club *club, t_sprite *s)
{
	t_img		*tex;
	int			x;
	int			y;
	int			color;
	int			tex_x;
	int			tex_y;
	int			y_start;
	int			y_end;
	int			jump;

	// 选取当前精灵类型对应的纹理
	if (s->type < 0 || s->type >= SPRITE_TYPES)
		return ;
	tex = &club->sprite_textures[s->type];
	if (!tex->img || !tex->addr || tex->width <= 0 || tex->height <= 0)
		return ;
	x = s->screen_x - s->width / 2;
	while (x < s->screen_x + s->width / 2)
	{
		if (x >= 0 && x < WIDTH && s->transform_y > 0 && s->transform_y < club->z_buffer[x])
		{
			tex_x = (x - (s->screen_x - s->width / 2)) * tex->width / s->width;
			y_start = -s->height / 2 + HEIGHT / 2;
			y_end = s->height / 2 + HEIGHT / 2;
			jump = (int)(sin(club->sprite_jump * 0.12 + s->phase) * 6.0);
			y_start += jump;
			y_end += jump;
			if (y_start < 0)
				y_start = 0;
			if (y_end >= HEIGHT)
				y_end = HEIGHT - 1;
			y = y_start;
			while (y <= y_end)
			{
				tex_y = (y - y_start) * tex->height / (y_end - y_start + 1);
				color = *((int *)(tex->addr
					+ (tex_y * tex->line_len
					+ tex_x * (tex->bpp / 8))));
				if ((color & 0x00FFFFFF) != 0)
					put_pixel(&club->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}

// static void	draw_sprite_pixel(t_club *club, t_sprite *s)
// {
// 	int			x;
// 	int			y;
// 	int			color;
// 	int			tex_x;
// 	int			tex_y;
// 	int			y_start;
// 	int			y_end;
// 	int			jump;

// 	x = s->screen_x - s->width / 2; 
// 	while (x < s->screen_x + s->width / 2)
// 	{
// 		if (x >= 0 && x < WIDTH && s->transform_y > 0 && s->transform_y < club->z_buffer[x])
// 		{
// 			tex_x = (x - (s->screen_x - s->width / 2)) * club->sprite_texture.width / s->width;
// 			y_start = -s->height / 2 + HEIGHT / 2;
// 			y_end = s->height / 2 + HEIGHT / 2;

// 			jump = (int)(sin(club->sprite_jump * 0.12 + s->phase) * 6.0);
// 			y_start += jump;
// 			y_end   += jump;

// 			// clamp 到屏幕范围
// 			if (y_start < 0)
// 				y_start = 0;
// 			if (y_end >= HEIGHT)
// 				y_end = HEIGHT - 1;

// 			y = y_start;
// 			while (y <= y_end)
// 			{
// 				tex_y = (y - y_start) * club->sprite_texture.height
// 					/ (y_end - y_start + 1);

// 				color = *((int *)(club->sprite_texture.addr
// 					+ (tex_y * club->sprite_texture.line_len
// 					+ tex_x * (club->sprite_texture.bpp / 8))));

// 				if ((color & 0x00FFFFFF) != 0)
// 					put_pixel(&club->img, x, y, color);
// 				y++;
// 			}
// 		}
// 		x++;
// 	}
// }

void	render_sprites(t_club *club)
{
	int	i;

	i = 0;
	while (i < club->sprite_count)
	{
		calc_sprite_info(club, &club->sprites[i]);
		i++;
	}
	sort_sprites(club);
	i = 0;
	while (i < club->sprite_count)
	{
		draw_sprite_pixel(club, &club->sprites[i]);
		i++;
	}
}

