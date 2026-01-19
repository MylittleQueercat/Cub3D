/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguo <hguo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:26:07 by hguo              #+#    #+#             */
/*   Updated: 2026/01/19 16:26:08 by hguo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	save_door_hit(t_club *c, t_step *s, t_ray *r)
{
	double	dist;
	double	hp;

	if (r->has_door)
		return ;
	if (s->side == 0)
		dist = (s->map_x - c->player.x
				+ (1 - s->step_x) / 2.0) / r->ray_dir_x;
	else
		dist = (s->map_y - c->player.y
				+ (1 - s->step_y) / 2.0) / r->ray_dir_y;
	if (dist <= 0.0001)
		return ;
	r->has_door = 1;
	r->door_dist = dist;
	r->door_side = s->side;
	if (s->side == 0)
		hp = c->player.y + dist * r->ray_dir_y;
	else
		hp = c->player.x + dist * r->ray_dir_x;
	r->door_hit_point = hp - floor(hp);
}

int	handle_door_cell(t_club *c, t_step *s, t_ray *r)
{
	t_door	*d;

	save_door_hit(c, s, r);
	d = door_at(c, s->map_x, s->map_y);
	if (d && d->state == DOOR_OPEN)
		return (0);
	r->hit_type = HIT_DOOR;
	r->side = s->side;
	r->hit_map_x = s->map_x;
	r->hit_map_y = s->map_y;
	return (1);
}

static void	init_single_door(t_club *club, int x, int y, int *i)
{
	club->doors[*i].x = x;
	club->doors[*i].y = y;
	club->doors[*i].state = DOOR_CLOSED;
	club->doors[*i].t = 0.0;
	(*i)++;
}

static void	scan_door_row(t_club *club, int y, int *i)
{
	int	x;

	x = 0;
	while (x < club->map.width)
	{
		if (club->map.grid[y][x] == 'D')
			init_single_door(club, x, y, i);
		x++;
	}
}

bool	init_doors(t_club *club)
{
	int	y;
	int	i;

	club->door_count = count_char_in_map(club->map.grid, 'D');
	if (club->door_count <= 0)
		return (true);
	club->doors = ft_calloc(club->door_count, sizeof(t_door));
	if (!club->doors)
		return (false);
	i = 0;
	y = 0;
	while (y < club->map.height)
	{
		scan_door_row(club, y, &i);
		y++;
	}
	return (true);
}

// bool	init_doors(t_club *club)
// {
// 	int	x;
// 	int	y;
// 	int	i;

// 	club->door_count = count_char_in_map(club->map.grid, 'D');
// 	if (club->door_count <= 0)
// 		return (true);
// 	club->doors = ft_calloc(club->door_count, sizeof(t_door));
// 	if (!club->doors)
// 		return (false);
// 	i = 0;
// 	y = 0;
// 	while (y < club->map.height)
// 	{
// 		x = 0;
// 		while (x < club->map.width)
// 		{
// 			if (club->map.grid[y][x] == 'D')
// 			{
// 				club->doors[i].x = x;
// 				club->doors[i].y = y;
// 				club->doors[i].state = DOOR_CLOSED;
// 				club->doors[i].t = 0.0;
// 				i++;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (true);
// }

// t_door	*door_at(t_club *c, int mx, int my)
// {
// 	int	i;

// 	i = 0;
// 	while (i < c->door_count)
// 	{
// 		if ((int)c->doors[i].x == mx && (int)c->doors[i].y == my)
// 			return (&c->doors[i]);
// 		i++;
// 	}
// 	return (NULL);
// }

// void	try_open_door(t_club *c)
// {
// 	double	fx;
// 	double	fy;
// 	int		mx;
// 	int		my;
// 	t_door	*d;

// 	fx = c->player.x + c->player.dir_x * 1.8;
// 	fy = c->player.y + c->player.dir_y * 1.8;
// 	mx = (int)fx;
// 	my = (int)fy;
// 	if (my < 0 || my >= c->map.height || mx < 0 || mx >= c->map.width)
// 		return ;
// 	if (c->map.grid[my][mx] != 'D')
// 		return ;
// 	printf("O pressed: door_count=%d\n", c->door_count);
// 	printf("target cell (%d,%d)=%c\n", mx, my, c->map.grid[my][mx]);
// 	d = door_at(c, mx, my);
// 	printf ("door_at returned %p\n", (void *)d);
// 	if (!d)
// 		return ;
// 	if (d->state == DOOR_CLOSED)
// 		d->state = DOOR_OPENING;
// 	else if (d->state == DOOR_OPEN)
// 		d->state = DOOR_CLOSING;
// }

// static void	save_door_hit(t_club *c, t_step *s, t_ray *r)
// {
// 	double	dist;
// 	double	hp;

// 	if (r->has_door)
// 		return ;
// 	if (s->side == 0)
// 		dist = (s->map_x - c->player.x
// 				+ (1 - s->step_x) / 2.0) / r->ray_dir_x;
// 	else
// 		dist = (s->map_y - c->player.y
// 				+ (1 - s->step_y) / 2.0) / r->ray_dir_y;
// 	if (dist <= 0.0001)
// 		return ;
// 	r->has_door = 1;
// 	r->door_dist = dist;
// 	r->door_side = s->side;
// 	if (s->side == 0)
// 		hp = c->player.y + dist * r->ray_dir_y;
// 	else
// 		hp = c->player.x + dist * r->ray_dir_x;
// 	r->door_hit_point = hp - floor(hp);
// }

// int	handle_door_cell(t_club *c, t_step *s, t_ray *r)
// {
// 	t_door	*d;

// 	save_door_hit(c, s, r);
// 	d = door_at(c, s->map_x, s->map_y);
// 	if (d && d->state == DOOR_OPEN)
// 		return (0);
// 	r->hit_type = HIT_DOOR;
// 	r->side = s->side;
// 	r->hit_map_x = s->map_x;
// 	r->hit_map_y = s->map_y;
// 	return (1);
// }

// void	update_doors(t_club *c)
// {
// 	int		i;
// 	double	speed;

// 	speed = 0.08;
// 	i = 0;
// 	while (i < c->door_count)
// 	{
// 		if (c->doors[i].state == DOOR_OPENING)
// 		{
// 			c->doors[i].t += speed;
// 			if (c->doors[i].t >= 1.0)
// 			{
// 				c->doors[i].t = 1.0;
// 				c->doors[i].state = DOOR_OPEN;
// 			}
// 		}
// 		else if (c->doors[i].state == DOOR_CLOSING)
// 		{
// 			c->doors[i].t -= speed;
// 			if (c->doors[i].t <= 0.0)
// 			{
// 				c->doors[i].t = 0.0;
// 				c->doors[i].state = DOOR_CLOSED;
// 			}
// 		}
// 		i++;
// 	}
// }
