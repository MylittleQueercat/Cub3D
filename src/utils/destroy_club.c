#include "../include/cub3d.h"

void	destroy_club(t_club *club)
{
	if (!club)
		return ;
	destroy_sprites(club);
	destroy_doors(club);
	destroy_textures_club(club);
	destroy_map(club);
	if (club->img.img)
		mlx_destroy_image(club->mlx, club->img.img);
	if (club->win)
		mlx_destroy_window(club->mlx, club->win);
	if (club->sprite_texture.img)
	{
		mlx_destroy_image(club->mlx, club->sprite_texture.img);
		club->sprite_texture.img = NULL;
	}

	if (club->win_img.img)
	{
		mlx_destroy_image(club->mlx, club->win_img.img);
		club->win_img.img = NULL;
	}
	club->win_loaded = 0;
}
