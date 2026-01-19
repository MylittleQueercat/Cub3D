#include "../include/cub3d.h"

// // 根据射线的方向和碰撞的面，选择 NO / SO / WE / EA
// static int	choose_texture(t_ray *r)
// {
// 	if (r->side == 0)
// 	{
// 		if (r->ray_dir_x > 0)
// 			return (TEX_WE);
// 		else
// 			return (TEX_EA);
// 	}
// 	else
// 	{
// 		if (r->ray_dir_y > 0)
// 			return (TEX_NO);
// 		else
// 			return (TEX_SO);
// 	}
// }

// void	draw_wall_stripe(t_club *club, int x, t_ray *r)
// {
// 	int		tex_id;
// 	t_tex	*tex;
// 	double	wall_x;
// 	int		tex_x;
// 	double	step;
// 	double	tex_pos;
// 	int		y;

// 	if (r->line_height <= 0)
// 		return ;
// 	if (r->draw_start < 0)
// 		r->draw_start = 0;
// 	if (r->draw_end >= HEIGHT)
// 		r->draw_end = HEIGHT - 1;
// 	tex = NULL;
// 	if (r->hit_type == HIT_DOOR)
// 		tex = &club->door_tex;
// 	else
// 	{
// 		tex_id = choose_texture(r);
// 		tex = &club->tex[tex_id];
// 	}
// 	if (!tex->img || !tex->addr || tex->width <= 0 || tex->height <= 0)
// 		return ;
// 	if (r->side == 0)
// 		wall_x = club->player.y + r->perp_wall_dist * r->ray_dir_y;
// 	else
// 		wall_x = club->player.x + r->perp_wall_dist * r->ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * (double)tex->width);
// 	if (r->side == 0 && r->ray_dir_x > 0)
// 		tex_x = tex->width - tex_x - 1;
// 	if (r->side == 1 && r->ray_dir_y < 0)
// 		tex_x = tex->width - tex_x - 1;
// 	if (r->hit_type == HIT_DOOR)
// 	{
// 		t_door	*d;
// 		int		shift;

// 		d = door_at(club, r->hit_map_x, r->hit_map_y);
// 		if (d)
// 		{
// 			shift = (int)(d->t * (double)tex->width);
// 			tex_x += shift;
// 		}
// 	}
// 	step = 1.0 * tex->height / r->line_height;
// 	tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * step;
// 	y = r->draw_start;
// 	while (y < r->draw_end)
// 	{
// 		int		tex_y;
// 		char	*pixel;
// 		int		color;
// 		tex_y = (int)tex_pos;
// 		if (tex_y < 0)
// 			tex_y = 0;
// 		if (tex_y >= tex->height)
// 			tex_y = tex->height - 1;
// 		tex_pos += step;
// 		if (r->hit_type == HIT_DOOR && (tex_x < 0 || tex_x >= tex->width))
// 		{
// 			y++;
// 			continue ;
// 		}
// 		pixel = tex->addr
// 			+ tex_y * tex->line_len
// 			+ tex_x * (tex->bpp / 8);
// 		color = *(int *)pixel;
// 		put_pixel(&club->img, x, y, color);
// 		y++;
// 	}
// }

void	draw_wall_stripe(t_club *club, int x, t_ray *r)
{
	t_stripe	st;

	if (r->line_height <= 0)
		return ;
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
	select_stripe_tex(club, r, &st);
	if (!st.tex || !st.tex->img || !st.tex->addr
		|| st.tex->width <= 0 || st.tex->height <= 0)
		return ;
	st.tex_x = compute_stripe_tex_x(club, r, st.tex);
	apply_door_shift(club, r, &st);
	st.step = 1.0 * st.tex->height / r->line_height;
	st.tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * st.step;
	st.y = r->draw_start;
	draw_stripe_column(club, x, r, &st);
}

// 判断某个格子是不是墙
int	is_wall(t_club *club, int map_x, int map_y)
{
	char	cell;
	t_door	*d;

	if (map_x < 0 || map_x >= club->map.width
		|| map_y < 0 || map_y >= club->map.height)
		return (1);
	cell = club->map.grid[map_y][map_x];
	if (cell == '1')
		return (1);
	if (cell == 'D')
	{
		d = door_at(club, map_x, map_y);
		if (!d)
			return (0);
		if (d->state != DOOR_OPEN)
			return (1);
	}
	return (0);
}
