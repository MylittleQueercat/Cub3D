#include "../include/cub3d.h"

static int	sprite_type_from_char(char c)
{
	if (c == '2')
		return (SPR_PONY);
	if (c == '3')
		return (SPR_SPARKLE);
	if (c == '4')
		return (SPR_HEART);
	if (c == '5')
		return (SPR_DISCO);
	return (-1);
}

bool	fill_sprite_array(t_club *club)
{
	int	y;
	int	x;
	int	idx;
	int	type;

	y = 0;
	idx = 0;
	while (club->map.grid[y] && idx < club->sprite_count)
	{
		x = 0;
		while (club->map.grid[y][x] && idx < club->sprite_count)
		{
			type = sprite_type_from_char(club->map.grid[y][x]);
			if (type != -1)
			{
				club->sprites[idx].x = x + 0.5;
				club->sprites[idx].y = y + 0.5;
				club->sprites[idx].type = type;
				club->sprites[idx].radius = 0.6;
				club->sprites[idx].visible = false;
				club->sprites[idx].distance = 0;
				club->sprites[idx].phase = (y * 7 + x * 13) * 0.37;
				club->sprites[idx].found = false;
				club->map.grid[y][x] = '0';
				idx++;
			}
			x++;
		}
		y++;
	}
	return (true);
}
