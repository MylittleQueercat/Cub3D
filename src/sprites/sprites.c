#include "../include/cub3d.h"

static int	count_char_in_map(char **map, char target)
{
	int	count;
	int	x;
	int	y;

	if (!map)
		return (0);
	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == target)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static bool	fill_sprite_array(t_club *club)
{
	int	y;
	int	x;
	int	idx;

	y = 0;
	idx = 0;
	while (club->map.grid[y])
	{
		x = 0;
		while (club->map.grid[y][x])
		{
			if (club->map.grid[y][x] == '2')
			{
				club->sprites[idx].x = x + 0.5;
				club->sprites[idx].y = y + 0.5;
				club->sprites[idx].visible = false;
				club->sprites[idx].distance = 0;
				club->sprites[idx].texture = "sprite.xpm";  // 以后再替换成实际贴图
				idx++;
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	find_sprite_position(t_club *club)
{
	if (!club || !club->map.grid)
		return (false);
	club->sprite_count = count_char_in_map(club->map.grid, '2');
	if (club->sprite_count == 0)
		return (false);
	club->sprites = malloc(sizeof(t_sprite) * club->sprite_count);
	if (!club->sprites)
		return (false);
	return (fill_sprite_array(club));
}

int	get_sprite_info(t_club *club)
{
	int	i;
	double	dx;
	double	dy;

	if (!club || !club->sprites || club->sprite_count == 0)
		return (-1);
	i = 0;
	while (i < club->sprite_count)
	{
		dx = club->sprites[i].x - club->player.x;
		dy = club->sprites[i].y - club->player.y;
		club->sprites[i].distance = (dx * dx) + (dy * dy);
		club->sprites[i].sprite_angle = atan2(dy, dx)
			- atan2(club->player.dir_y, club->player.dir_x);
		i++;
	}
	return (0);
}

int	sort_sprites(t_club *club)
{
	int	i;
	int	j;
	t_sprite tmp;

	if (!club || !club->sprites || club->sprite_count == 0)
		return (-1);
	i = 0;
	while (i < club->sprite_count - 1)
	{
		j = 0;
		while (j < club->sprite_count - 1 - i)
		{
			if (club->sprites[j].distance < club->sprites[j + 1].distance)
			{
				tmp = club->sprites[j];
				club->sprites[j] = club->sprites[j + 1];
				club->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	project_sprite(t_club *club, t_sprite *s)
{
	double	dist;
	double	view_dist;

	dist = sqrt(s->distance);
	view_dist = (WIDTH / 2.0) / tan(FOV / 2.0);
	s->screen_x = (int)(WIDTH / 2 + tan(s->sprite_angle) * view_dist);
	s->height = (int)(HEIGHT / dist);
	s->width = s->height;
}

void draw_sprite_pixel(t_img *img, t_club *club, t_sprite *s)
{

  
}

void render_sprites(t_club *club, t_img *img)
{
    int i;

    compute_sprite_info(club);
    sort_sprites(club);
    i = 0;
    while (i < club->sprite_count)
    {
        project_sprite(club, &club->sprites[i]);
        draw_sprite_pixel(img, club, &club->sprites[i]);
        i++;
    }
}
