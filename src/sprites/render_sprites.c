/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:30:39 by hguo              #+#    #+#             */
/*   Updated: 2026/01/19 16:30:40 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	inv_det = 1.0 / (club->player.plane_x * club->player.dir_y \
			- club->player.dir_x * club->player.plane_y);
	s->transform_x = inv_det * \
		(club->player.dir_y * dx - club->player.dir_x * dy);
	s->transform_y = inv_det * \
		(-club->player.plane_y * dx + club->player.plane_x * dy);
	s->visible = (s->transform_y > 0.0001);
	if (!s->visible)
		return ;
	ty = s->transform_y;
	if (ty < 0.35)
		ty = 0.35;
	s->screen_x = (int)((WIDTH / 2) * (1 + s->transform_x / ty));
	s->height = abs((int)((HEIGHT / ty) * 0.8));
	if (s->height > (int)(HEIGHT * 0.90))
		s->height = (int)(HEIGHT * 0.90);
	s->width = s->height;
}

static void	sort_sprites(t_club *club)
{
	int			i;
	int			j;
	t_sprite	tmp;

	if (!club->sprites || club->sprite_count < 2)
		return ;
	i = 0;
	while (i < club->sprite_count - 1)
	{
		j = i + 1;
		while (j < club->sprite_count)
		{
			if (club->sprites[i].distance < club->sprites[j].distance)
			{
				tmp = club->sprites[i];
				club->sprites[i] = club->sprites[j];
				club->sprites[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	draw_sprite_column(t_club *club, t_sprite *s, t_img *tex, int x)
{
	int	y;
	int	tex_y;
	int	color;
	int	y_range[2];
	int	jump;

	jump = (int)(sin(club->sprite_jump * 0.12 + s->phase) * 6.0);
	y_range[0] = fmax(0, -s->height / 2 + HEIGHT / 2 + jump);
	y_range[1] = fmin(HEIGHT - 1, s->height / 2 + HEIGHT / 2 + jump);
	y = y_range[0];
	while (y <= y_range[1])
	{
		tex_y = (y - y_range[0]) * tex->height / (y_range[1] - y_range[0] + 1);
		color = *(int *)(tex->addr + (tex_y * tex->line_len \
				+ ((x - (s->screen_x - s->width / 2)) * tex->width / s->width) \
				* (tex->bpp / 8)));
		if ((color & 0x00FFFFFF) != 0)
			put_pixel(&club->img, x, y, color);
		y++;
	}
}

static void	draw_sprite_pixel(t_club *club, t_sprite *s)
{
	t_img	*tex;
	int		x;
	int		start_x;

	if (s->type < 0 || s->type >= SPRITE_TYPES)
		return ;
	tex = &club->sprite_textures[s->type];
	if (!tex->img || !tex->addr || tex->width <= 0 || tex->height <= 0)
		return ;
	start_x = s->screen_x - s->width / 2;
	x = start_x - 1;
	while (++x < s->screen_x + s->width / 2)
	{
		if (x >= 0 && x < WIDTH && s->transform_y > 0 \
			&& s->transform_y < club->z_buffer[x])
			draw_sprite_column(club, s, tex, x);
	}
}

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
