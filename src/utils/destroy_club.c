#include "../include/cub3d.h"

static void	destroy_doors(t_club *club)
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

static void	destroy_sprites(t_club *club)
{
	int	i;

	if (!club || !club->sprites)
		return ;
	i = 0;
	while (i < club->sprite_count)
	{
		if (club->sprites[i].img.img)
			mlx_destroy_image(club->mlx, club->sprites[i].img.img);
		i++;
	}
	free(club->sprites);
	club->sprites = NULL;
	club->sprite_count = 0;
}

static void	destroy_textures_club(t_club *club)
{
	int	i;

	if (!club)
		return ;
	if (club->door_tex.path)
		free(club->door_tex.path);
	if (club->door_open_tex.path)
		free(club->door_open_tex.path);
	i = 0;
	while (i < TEX_COUNT)
	{
		if (club->tex[i].path)
			free(club->tex[i].path);
		// if (club->tex[i].img.img)
		// 	mlx_destroy_image(club->mlx, club->tex[i].img.img);
		i++;
	}
}

static void	destroy_map(t_club *club)
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
}
