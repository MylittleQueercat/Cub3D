#include "../include/cub3d.h"

static int	get_sprite_info(t_club *club)
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

static int	sort_sprites(t_club *club)
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

/*
** Projects a sprite from world space onto the screen using the angle method.
**
** - `s->distance` is the squared distance from the player to the sprite.
**   We take the square root to get the real distance, which is used to scale
**   the sprite size on screen (closer = bigger, farther = smaller).
**
** - `view_dist` represents the distance from the player to the projection
**   plane (screen). It is derived from the screen width and the field of view
**   (FOV), and is used to convert an angle into a horizontal screen offset.
**
** - `s->screen_x` is the horizontal center position of the sprite on screen.
**   It is computed by projecting the sprite's relative angle (`sprite_angle`)
**   onto the screen using a tangent-based projection.
**
** - `s->height` and `s->width` define the sprite's size on screen.
**   The size is inversely proportional to the distance to the player.
*/
static void project_sprite(t_sprite *s)
{
    double dist;
    double view_dist;

    dist = sqrt(s->distance);
    view_dist = (WIDTH / 2.0) / tan(FOV / 2.0);
    s->screen_x = (int)(WIDTH / 2 + tan(s->sprite_angle) * view_dist);
    s->height = (int)((0.5 * view_dist / dist) * 0.5);
    s->width = s->height;
}


static void	draw_sprite_pixel(t_img *img, t_club *club, t_sprite *s)
{
	int		x;
	int		y;
	int		screen_x;
	int		screen_y;
	int		tex_x;
	int		tex_y;
	int		color;

	if (!club || !s || !club->sprite_texture.img)
		return ;

	x = -s->width / 2;
	while (x < s->width / 2)
	{
		screen_x = s->screen_x + x;
		if (screen_x >= 0 && screen_x < WIDTH
			&& sqrt(s->distance) < club->z_buffer[screen_x])
		{
			y = -s->height / 2;
			while (y < s->height / 2)
			{
				screen_y = HEIGHT / 2 + y;
				if (screen_y >= 0 && screen_y < HEIGHT)
				{
					// 计算纹理坐标
					tex_x = (x + s->width / 2) * club->sprite_texture.width / s->width;
					tex_y = (y + s->height / 2) * club->sprite_texture.height / s->height;

					// 获取纹理颜色
					color = *((int *)(club->sprite_texture.addr + (tex_y * club->sprite_texture.line_len + tex_x * (club->sprite_texture.bpp / 8))));

					// 忽略透明色（假设 0x00FFFFFF 以下为透明）
					if ((color & 0x00FFFFFF) != 0)
						put_pixel(img, screen_x, screen_y, color);
				}
				y++;
			}
		}
		x++;
	}
}

void render_sprites(t_club *club, t_img *img)
{
    int i;

    get_sprite_info(club);
    sort_sprites(club);
    i = 0;
    while (i < club->sprite_count)
    {
        project_sprite(&club->sprites[i]);
        draw_sprite_pixel(img, club, &club->sprites[i]);
        i++;
    }
}

