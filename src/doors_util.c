#include "../include/cub3d.h"

t_door *door_at(t_club *c, int mx, int my)
{
    for (int i = 0; i < c->door_count; i++)
    {
        if ((int)c->doors[i].x == mx && (int)c->doors[i].y == my)
            return &c->doors[i];
    }
    return NULL;
}

void	try_open_door(t_club *c)
{
    double	fx;
    double	fy;
    int		mx;
    int		my;
	t_door	*d;

	fx = c->player.x + c->player.dir_x * 0.8;
	fy = c->player.y + c->player.dir_y * 0.8;
    mx = (int)fx;
    my = (int)fy;
    if (my < 0 || my >= c->map.height || mx < 0 || mx >= c->map.width)
        return ;
    if (c->map.grid[my][mx] != 'D')
        return ;
    d = door_at(c, mx, my);
    if (!d)
		return ;
    d->is_open = !d->is_open;
}

static void	save_door_hit(t_club *c, t_step *s, t_ray *r)
{
    double dist;
    double hp;

    if (r->has_door)
        return ;
	if (dist <= 0.0001)
		return ;
    if (s->side == 0)
        dist = (s->map_x - c->player.x + (1 - s->step_x) / 2.0) / r->ray_dir_x;
    else
        dist = (s->map_y - c->player.y + (1 - s->step_y) / 2.0) / r->ray_dir_y;
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
    t_door *d;

    save_door_hit(c, s, r);
    d = door_at(c, s->map_x, s->map_y);
    if (d && d->is_open)
        return (0);
    r->hit_type = HIT_DOOR;
    r->side = s->side;
    r->hit_map_x = s->map_x;
    r->hit_map_y = s->map_y;
    return (1);
}


