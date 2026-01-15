#include "../include/cub3d.h"

// void update_collectibles(t_club *club)
// {
//     int i;
//     double r; // 找到半径

//     if (!club->sprites || club->sprite_count <= 0 || club->game_won)
//         return;

//     r = 0.55;
//     i = 0;
//     while (i < club->sprite_count)
//     {
//         t_sprite *s = &club->sprites[i];
//         if (!s->found)
//         {
//             double dx = club->player.x - s->x;
//             double dy = club->player.y - s->y;
//             if (dx*dx + dy*dy <= r*r)
//             {
//                 s->found = true;
//                 club->found_count++;
//                 if (club->found_count == club->sprite_count)
//                     club->game_won = 1;
//             }
//         }
//         i++;
//     }
// }

void	update_collectibles(t_club *club)
{
	int				i;
	t_sprite		*s;
	double			dx;
	double			dy;
	double			r;

	if (!club->sprites || club->sprite_count <= 0 || club->game_won)
		return ;
	i = 0;
	while (i < club->sprite_count)
	{
		s = &club->sprites[i];
		if (!s->found)
		{
			dx = club->player.x - s->x;
			dy = club->player.y - s->y;
			const double	pr = 0.25;
			r = pr + s->radius + 0.05;
			if (dx * dx + dy * dy <= r * r)
			{
				s->found = true;
				club->found_count++;
				if (club->found_count == club->sprite_count)
					club->game_won = 1;
			}
		}
		i++;
	}
}
