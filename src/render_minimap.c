#include "../include/cub3d.h"

// void    render_minimap(t_club *club)
// {
//     int     x;
//     int     y;
//     int     tile;
//     int     map_x;
//     int     map_y;
//     char    **g;

//     tile = 17;
//     y = 0;
//     g = club->map.grid;
//     while (y < club->map.height)
//     {
//         x = 0;
//         while (x < club->map.width - 1)
//         {
//             if (g[y][x] == '1')
//                 mm_draw_square(&club->img, x * tile, y * tile, tile, MM_WALL);
//             else if (g[y][x] == 'D')
//                 mm_draw_square(&club->img, x * tile, y * tile, tile, MM_DOOR);
//             else
//                 mm_draw_square(&club->img, x * tile, y * tile, tile, MM_BG);
//             x++;
//         }
//         y++;
//     }
//     map_x = (int)(club->player.x * tile);
//     map_y = (int)(club->player.y * tile);
//     mm_draw_player_pony(&club->img, map_x, map_y, tile);
//     int i = 0;
//     while (i < club->sprite_count)
//     {
//         if (club->sprites[i].found)
//         {
//             int sx = (int)(club->sprites[i].x * tile);
//             int sy = (int)(club->sprites[i].y * tile);
//             mm_draw_sprite(&club->img, sx, sy, tile);
//         }
//         i++;
//     }
// }

static int	mm_tile_px(void)
{
	int	t;

	t = MM_W / (2 * MM_R + 1);
	if (t < 4)
		t = 4;
	return (t);
}

static void	mm_clear(t_club *club)
{
	int	x;
	int	y;

	y = 0;
	while (y < MM_H)
	{
		x = 0;
		while (x < MM_W)
		{
			put_pixel(&club->img, MM_ORIGIN_X + x, MM_ORIGIN_Y + y, MM_BG);
			x++;
		}
		y++;
	}
}

static void	mm_draw_tiles(t_club *club, int px, int py, int tile)
{
	int		tx;
	int		ty;
	int		sx;
	int		sy;
	char	**g;

	g = club->map.grid;
	ty = py - MM_R;
	while (ty <= py + MM_R)
	{
		tx = px - MM_R;
		while (tx <= px + MM_R)
		{
			sx = MM_ORIGIN_X + (tx - (px - MM_R)) * tile;
			sy = MM_ORIGIN_Y + (ty - (py - MM_R)) * tile;
			if (ty < 0 || ty >= club->map.height
				|| tx < 0 || tx >= club->map.width)
				mm_draw_square(&club->img, sx, sy, tile, MM_BG);
			else
				mm_draw_square(&club->img, sx, sy, tile,
					mm_color_for_cell(g[ty][tx]));
			tx++;
		}
		ty++;
	}
}

static void	mm_draw_sprites_in_view(t_club *club, int tile)
{
	int		i;
	double	dx;
	double	dy;
	int		msx;
	int		msy;

	i = 0;
	while (i < club->sprite_count)
	{
		if (club->sprites[i].found)
		{
			dx = club->sprites[i].x - club->player.x;
			dy = club->sprites[i].y - club->player.y;
			msx = MM_ORIGIN_X + MM_R * tile + (int)(dx * tile);
			msy = MM_ORIGIN_Y + MM_R * tile + (int)(dy * tile);
			if (msx >= MM_ORIGIN_X && msx < MM_ORIGIN_X + MM_W
				&& msy >= MM_ORIGIN_Y && msy < MM_ORIGIN_Y + MM_H)
				mm_draw_sprite(&club->img, msx, msy, tile);
		}
		i++;
	}
}

void	render_minimap(t_club *club)
{
	int	tile;
	int	px;
	int	py;

	tile = mm_tile_px();
	px = (int)club->player.x;
	py = (int)club->player.y;
	mm_clear(club);
	mm_draw_tiles(club, px, py, tile);
	mm_draw_player_pony(&club->img,
		MM_ORIGIN_X + MM_R * tile + (int)((club->player.x - px) * tile),
		MM_ORIGIN_Y + MM_R * tile + (int)((club->player.y - py) * tile),
		tile);
	mm_draw_sprites_in_view(club, tile);
}
