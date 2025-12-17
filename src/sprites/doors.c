#include "../include/cub3d.h"

static bool fill_door_array(t_club *club)
{
	int y;
	int x;
	int idx;

	y = 0;
	idx = 0;
	while (club->map.grid[y] && idx < club->door_count)
	{
		x = 0;
		while (club->map.grid[y][x] && idx < club->door_count)
		{
			if (club->map.grid[y][x] == 'D')
			{
				club->doors[idx].x = x + 0.5;
				club->doors[idx].y = y + 0.5;
				club->doors[idx].is_open = true;
				club->doors[idx].visible = false;
				club->doors[idx].img_closed.img = NULL;
				club->doors[idx].img_open.img = NULL;
				idx++;
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool init_doors(t_club *club)
{
	if (!club || !club->map.grid)
		return (false);
	club->door_count = count_char_in_map(club->map.grid, 'D');
	// printf("door number %d\n", club->door_count);

	if (club->door_count == 0)
		return (false);
	club->doors = malloc(sizeof(t_door) * club->door_count);
	if (!club->doors)
		return (false);
	if (!fill_door_array(club))
	{
		free(club->doors);
		club->doors = NULL;
		return (false);
	}
	return (true);
}

/*
** try_open_door:
** Checks the map cell directly in front of the player.
** If it contains a closed door ('D'), mark it as open and update the map to '0'
** so the player can walk through.
*/
void try_open_door(t_club *club)
{
	int i;
	int check_x;
	int check_y;

	if (!club || !club->doors || !club->map.grid)
		return;
	check_x = (int)(club->player.x + club->player.dir_x);
	check_y = (int)(club->player.y + club->player.dir_y);
	i = 0;
	while (i < club->door_count)
	{
		if ((int)(club->doors[i].x) == check_x && (int)(club->doors[i].y) == check_y && club->doors[i].is_open == false)
		{
			club->doors[i].is_open = true;
			club->map.grid[check_y][check_x] = '0';
			return;
		}
		i++;
	}
}

int load_door_textures(t_club *club)
{
	int i;
	char *closed_path;
	char *open_path;

	if (!club || !club->doors || !club->mlx)
		return (1);
	closed_path = "textures/door_closed.xpm";
	open_path = "textures/door_open1.xpm";
	if (!is_valid_xpm_file(closed_path) || !is_valid_xpm_file(open_path))
		return (err_msg("Error: door texture XPM missing"), 1);
	i = 0;
	while (i < club->door_count)
	{
		club->doors[i].img_closed.img = mlx_xpm_file_to_image(club->mlx,
															  closed_path,
															  &club->doors[i].img_closed.width,
															  &club->doors[i].img_closed.height);
		club->doors[i].img_open.img = mlx_xpm_file_to_image(club->mlx,
															open_path,
															&club->doors[i].img_open.width,
															&club->doors[i].img_open.height);
		if (!club->doors[i].img_closed.img || !club->doors[i].img_open.img)
			return (1);
		club->doors[i].img_closed.addr = mlx_get_data_addr(
			club->doors[i].img_closed.img,
			&club->doors[i].img_closed.bpp,
			&club->doors[i].img_closed.line_len,
			&club->doors[i].img_closed.endian);
		club->doors[i].img_open.addr = mlx_get_data_addr(
			club->doors[i].img_open.img,
			&club->doors[i].img_open.bpp,
			&club->doors[i].img_open.line_len,
			&club->doors[i].img_open.endian);

		i++;
	}
	return (0);
}

void project_door(t_club *club, t_door *d)
{
	double dx;
	double dy;
	double dist;
	double view_dist;

	dx = d->x - club->player.x;
	dy = d->y - club->player.y;
	dist = sqrt(dx * dx + dy * dy);

	if (dist <= 0.0)
	{
		d->visible = false;
		return;
	}
	d->visible = true;
	view_dist = (WIDTH / 2.0) / tan(FOV / 2.0);
	d->screen_x = (int)((WIDTH / 2) + ((atan2(dy, dx) - atan2(club->player.dir_y, club->player.dir_x)) * view_dist));
	d->height = (int)(view_dist / dist);
	d->width = d->height;
	d->perp_dist = dist;
}

void draw_door_pixel(t_img *img, t_club *club, t_door *d)
{
	int x, y;
	int screen_x, screen_y;
	int tex_x, tex_y;
	int color;
	t_img *tex;

	if (!d->visible)
		return;

	tex = d->is_open ? &d->img_open : &d->img_closed;

	x = -d->width / 2;
	while (x < d->width / 2)
	{
		screen_x = d->screen_x + x;
		if (screen_x < 0 || screen_x >= WIDTH || d->perp_dist >= club->z_buffer[screen_x])
		{
			x++;
			continue;
		}

		y = -d->height / 2;
		while (y < d->height / 2)
		{
			screen_y = HEIGHT / 2 + y;

			tex_x = (x + d->width / 2) * tex->width / d->width;
			tex_y = (y + d->height / 2) * tex->height / d->height;

			color = *((int *)(tex->addr + tex_y * tex->line_len + tex_x * (tex->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(img, screen_x, screen_y, color);

			y++;
		}
		x++;
	}
}

void render_doors(t_club *club)
{
	int i;

	i = 0;
	while (i < club->door_count)
	{
		project_door(club, &club->doors[i]);
		draw_door_pixel(&club->img, club, &club->doors[i]);
		i++;
	}
}
