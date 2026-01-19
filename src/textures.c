#include "../include/cub3d.h"

static int	load_texture(t_club *club, t_tex *tex)
{
	tex->img = mlx_xpm_file_to_image(club->mlx,
			tex->path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(club->mlx, tex->img);
		tex->img = NULL;
		return (1);
	}
	return (0);
}

static void	try_load_tex(t_club *club, t_tex *tex, int *fail, int mandatory)
{
	int	err;

	if (!tex || !tex->path)
	{
		if (mandatory)
			*fail = 1;
		return ;
	}
	err = load_texture(club, tex);
	if (err)
	{
		tex->img = NULL;
		tex->addr = NULL;
		if (mandatory)
			*fail = 1;
	}
}

int	load_all_textures(t_club *club)
{
	int	fail;

	fail = 0;
	try_load_tex(club, &club->tex[TEX_NO], &fail, 1);
	try_load_tex(club, &club->tex[TEX_SO], &fail, 1);
	try_load_tex(club, &club->tex[TEX_WE], &fail, 1);
	try_load_tex(club, &club->tex[TEX_EA], &fail, 1);
	try_load_tex(club, &club->tex[TEX_CEIL], &fail, 0);
	try_load_tex(club, &club->tex[TEX_FLOOR], &fail, 0);
	try_load_tex(club, &club->door_tex, &fail, 1);
	try_load_tex(club, &club->door_open_tex, &fail, 1);
	return (fail);
}

static void	destroy_one_tex(t_club *c, t_tex *t, int free_path)
{
	if (t->img)
	{
		mlx_destroy_image(c->mlx, t->img);
		t->img = NULL;
		t->addr = NULL;
	}
	if (free_path && t->path)
	{
		free(t->path);
		t->path = NULL;
	}
}

void	destroy_textures(t_club *club)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		destroy_one_tex(club, &club->tex[i], 0);
		i++;
	}
	destroy_one_tex(club, &club->door_tex, 1);
	destroy_one_tex(club, &club->door_open_tex, 1);
}

// #include "../include/cub3d.h"

// static int	load_texture(t_club *club, t_tex *tex)
// {
// 	if (!tex || !tex->path)
// 	{
// 		printf("load_texture: NULL path\n");
// 		return (1);
// 	}
// 	tex->img = mlx_xpm_file_to_image(club->mlx,
// 			tex->path, &tex->width, &tex->height);
// 	if (!tex->img)
// 	{
// 		printf("mlx_xpm_file_to_image failed for %s\n", tex->path);
// 		return (1);
// 	}
// 	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
// 			&tex->line_len, &tex->endian);
// 	if (!tex->addr)
// 	{
// 		mlx_destroy_image(club->mlx, tex->img);
// 		tex->img = NULL;
// 		printf("mlx_get_data_addr failed for %s\n", tex->path);
// 		return (1);
// 	}
// 	return (0);
// }

// int	load_all_textures(t_club *club)
// {
// 	int	fail;

// 	fail = 0;
// 	printf("load_all_textures called\n");
// 	if (load_texture(club, &club->tex[TEX_NO]))
// 	{
// 		printf("Warning: failed to load TEX_NO\n");
// 		fail = 1;
// 		club->tex[TEX_NO].img = NULL;
// 	}
// 	if (load_texture(club, &club->tex[TEX_SO]))
// 	{
// 		printf("Warning: failed to load TEX_SO\n");
// 		fail = 1;
// 		club->tex[TEX_SO].img = NULL;
// 	}
// 	if (load_texture(club, &club->tex[TEX_WE]))
// 	{
// 		printf("Warning: failed to load TEX_WE\n");
// 		fail = 1;
// 		club->tex[TEX_WE].img = NULL;
// 	}
// 	if (load_texture(club, &club->tex[TEX_EA]))
// 	{
// 		printf("Warning: failed to load TEX_EA\n");
// 		fail = 1;
// 		club->tex[TEX_EA].img = NULL;
// 	}
// 	if (club->tex[TEX_CEIL].path && load_texture(club, &club->tex[TEX_CEIL]))
// 	{
// 		printf("Warning: failed to load TEX_CEIL, fallback to color\n");
// 		club->tex[TEX_CEIL].img = NULL;
// 	}
// 	if (club->tex[TEX_FLOOR].path && load_texture(club, &club->tex[TEX_FLOOR]))
// 	{
// 		printf("Warning: failed to load TEX_FLOOR, fallback to color\n");
// 		club->tex[TEX_FLOOR].img = NULL;
// 	}
// 	if (load_texture(club, &club->door_tex))
// 	{
// 		printf("Warning: failed to load door_tex (%s)\n", club->door_tex.path);
// 		fail = 1;
// 		club->door_tex.img = NULL;
// 	}
// 	if (load_texture(club, &club->door_open_tex))
// 	{
// 		printf("Warning: failed to load door_open_tex (%s)\n",
// 			club->door_open_tex.path);
// 		fail = 1;
// 		club->door_open_tex.img = NULL;
// 	}
// 	return (fail);
// }

// static void	destroy_one_tex(t_club *c, t_tex *t, int free_path)
// {
// 	if (t->img)
// 	{
// 		mlx_destroy_image(c->mlx, t->img);
// 		t->img = NULL;
// 		t->addr = NULL;
// 	}
// 	if (free_path && t->path)
// 	{
// 		free(t->path);
// 		t->path = NULL;
// 	}
// }

// void	destroy_textures(t_club *club)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		destroy_one_tex(club, &club->tex[i], 0);
// 		i++;
// 	}
// 	destroy_one_tex(club, &club->door_tex, 1);
// 	destroy_one_tex(club, &club->door_open_tex, 1);
// }
