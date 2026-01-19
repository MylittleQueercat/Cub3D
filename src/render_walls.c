#include "../include/cub3d.h"

// static void	set_ray_dir(t_club *club, t_ray *ray, int x)
// {
// 	double	camera_x;

// 	camera_x = 2.0 * x / (double)WIDTH - 1.0;
// 	ray->ray_dir_x = club->player.dir_x + club->player.plane_x * camera_x;
// 	ray->ray_dir_y = club->player.dir_y + club->player.plane_y * camera_x;
// }

// static void	init_step(t_club *club, t_ray *ray, t_step *s)
// {
// 	s->map_x = (int)club->player.x;
// 	s->map_y = (int)club->player.y;
// 	s->delta_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_x);
// 	s->delta_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray->ray_dir_y);
// 	if (ray->ray_dir_x < 0)
// 	{
// 		s->step_x = -1;
// 		s->dist_x = (club->player.x - s->map_x) * s->delta_x;
// 	}
// 	else
// 	{
// 		s->step_x = 1;
// 		s->dist_x = (s->map_x + 1.0 - club->player.x) * s->delta_x;
// 	}
// 	if (ray->ray_dir_y < 0)
// 	{
// 		s->step_y = -1;
// 		s->dist_y = (club->player.y - s->map_y) * s->delta_y;
// 	}
// 	else
// 	{
// 		s->step_y = 1;
// 		s->dist_y = (s->map_y + 1.0 - club->player.y) * s->delta_y;
// 	}
// }

// static void	walk_until_wall(t_club *club, t_step *s, t_ray *ray)
// {
// 	int	hit;

// 	hit = 0;
// 	ray->hit_type = HIT_NONE;
// 	while (!hit)
// 	{
// 		if (s->dist_x < s->dist_y)
// 		{
// 			s->dist_x += s->delta_x;
// 			s->map_x += s->step_x;
// 			s->side = 0;
// 		}
// 		else
// 		{
// 			s->dist_y += s->delta_y;
// 			s->map_y += s->step_y;
// 			s->side = 1;
// 		}
// 		if (club->map.grid[s->map_y][s->map_x] == '1')
// 		{
// 			ray->hit_type = HIT_WALL;
// 			ray->side = s->side;
// 			hit = 1;
// 		}
// 		else if (club->map.grid[s->map_y][s->map_x] == 'D')
// 			hit = handle_door_cell(club, s, ray);
// 	}
// }

// static void	compute_wall(t_ray *ray, t_step *s)
// {
// 	double	dist;

// 	if (s->side == 0)
// 		dist = s->dist_x - s->delta_x;
// 	else
// 		dist = s->dist_y - s->delta_y;
// 	if (dist < 0.0001)
// 		dist = 0.0001;
// 	ray->perp_wall_dist = dist;
// 	ray->line_height = (int)(HEIGHT / dist);
// 	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
// 	if (ray->draw_start < 0)
// 		ray->draw_start = 0;
// 	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
// 	if (ray->draw_end >= HEIGHT)
// 		ray->draw_end = HEIGHT - 1;
// 	ray->side = s->side;
// }

// void	draw_wall(t_club *club, int x, t_ray *ray)
// {
// 	if (ray->hit_type == HIT_WALL || ray->hit_type == HIT_DOOR)
// 		draw_wall_stripe(club, x, ray);
// }

// void	render_walls(t_club *club)
// {
// 	int		x;
// 	t_ray	ray;
// 	t_step	s;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		ray.has_door = 0;
// 		ray.door_dist = 0;
// 		set_ray_dir(club, &ray, x);
// 		init_step(club, &ray, &s);
// 		walk_until_wall(club, &s, &ray);
// 		compute_wall(&ray, &s);
// 		club->z_buffer[x] = ray.perp_wall_dist;
// 		draw_wall(club, x, &ray);
// 		x++;
// 	}
// }

#include "../include/cub3d.h"

static void	set_ray_dir(t_club *club, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->ray_dir_x = club->player.dir_x + club->player.plane_x * camera_x;
	ray->ray_dir_y = club->player.dir_y + club->player.plane_y * camera_x;
}

static void	init_ray_defaults(t_ray *ray)
{
	ray->has_door = 0;
	ray->door_dist = 0;
}

static void	draw_wall(t_club *club, int x, t_ray *ray)
{
	if (ray->hit_type == HIT_WALL || ray->hit_type == HIT_DOOR)
		draw_wall_stripe(club, x, ray);
}

void	render_walls(t_club *club)
{
	int		x;
	t_ray	ray;
	t_step	s;

	x = 0;
	while (x < WIDTH)
	{
		init_ray_defaults(&ray);
		set_ray_dir(club, &ray, x);
		init_step(club, &ray, &s);
		walk_until_wall(club, &s, &ray);
		compute_wall(&ray, &s);
		club->z_buffer[x] = ray.perp_wall_dist;
		draw_wall(club, x, &ray);
		x++;
	}
}
