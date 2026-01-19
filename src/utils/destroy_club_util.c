#include "../include/cub3d.h"

void	destroy_doors(t_club *club)
{
	int	i;

	if (!club || !club->doors)
		return ;
	i = 0;
	while (i < club->door_count)
	{
		if (club->doors[i].img_closed.img)
			mlx_destroy_image(club->mlx, club->doors[i].img_closed.img);
		if (club->doors[i].img_open.img)
			mlx_destroy_image(club->mlx, club->doors[i].img_open.img);
		i++;
	}
	free(club->doors);
	club->doors = NULL;
	club->door_count = 0;
}

// void	destroy_sprites(t_club *club)
// {
// 	int	i;

// 	if (!club || !club->sprites)
// 		return ;
// 	i = 0;
// 	while (i < club->sprite_count)
// 	{
// 		if (club->sprites[i].img.img)
// 			mlx_destroy_image(club->mlx, club->sprites[i].img.img);
// 		i++;
// 	}
// 	free(club->sprites);
// 	club->sprites = NULL;
// 	club->sprite_count = 0;
// }

void	destroy_sprites(t_club *club)
{
	if (!club)
		return ;
	if (club->sprites)
	{
		free(club->sprites);
		club->sprites = NULL;
	}
		club->sprite_count = 0;
}

void	destroy_tex(t_club *club, t_tex *t)
{
	if (!club || !t)
		return ;
	if (t->img)
	{
		mlx_destroy_image(club->mlx, t->img);
		t->img = NULL;
	}
	t->addr = NULL;
	if (t->path)
	{
		free(t->path);
		t->path = NULL;
	}
	t->width = 0;
	t->height = 0;
	t->bpp = 0;
	t->line_len = 0;
	t->endian = 0;
}

void	destroy_textures_club(t_club *club)
{
	int	i;

	if (!club)
		return ;
	i = 0;
	while (i < TEX_COUNT)
		destroy_tex(club, &club->tex[i++]);
	destroy_tex(club, &club->door_tex);
	destroy_tex(club, &club->door_open_tex);
}

void	destroy_map(t_club *club)
{
	int	i;

	if (!club || !club->map.grid)
		return ;
	i = 0;
	while (i < club->map.height)
	{
		if (club->map.grid[i])
			free(club->map.grid[i]);
		i++;
	}
	free(club->map.grid);
	club->map.grid = NULL;
	club->map.width = 0;
	club->map.height = 0;
}
