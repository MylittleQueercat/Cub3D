#include "../include/cub3d.h"

// static int	load_texture(t_club *club, t_tex *tex, char *path)
// {
// 	//读取.xpm文件，在内存里建图
// 	tex->img = mlx_xpm_file_to_image(club->mlx,
// 			path, &tex->width, &tex->height);
// 	if (!tex->img)
// 		return (1);
// 	//从图里拿到底层像素数据的地址
// 	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
// 			&tex->line_len, &tex->endian);
// 	if (!tex->addr)
// 		return (1);
// 	return (0);
// }

// int	load_all_textures(t_club *club)
// {
// 	if (load_texture(club, &club->tex[TEX_NO], "textures/no.xpm"))
// 		return (1);
// 	if (load_texture(club, &club->tex[TEX_SO], "textures/so.xpm"))
// 		return (1);
// 	if (load_texture(club, &club->tex[TEX_WE], "textures/we.xpm"))
// 		return (1);
// 	if (load_texture(club, &club->tex[TEX_EA], "textures/ea.xpm"))
// 		return (1);
// 	return (0);
// }

static int	load_texture(t_club *club, t_tex *tex)
{
	if (!tex || !tex->path)
		return (1);
	tex->img = mlx_xpm_file_to_image(club->mlx,
			tex->path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}


int	load_all_textures(t_club *club)
{
	if (load_texture(club, &club->tex[TEX_NO]) \
		|| load_texture(club, &club->tex[TEX_SO]) \
		|| load_texture(club, &club->tex[TEX_WE]) \
		|| load_texture(club, &club->tex[TEX_EA]))
		return (1);
	return (0);
}

// int	load_all_textures(t_club *club)
// {
// 	int fail = 0;

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

// 	// 可选：CEIL/FLOOR 纹理
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

// 	return (fail); // 0 表示全部加载成功，1 表示至少有一个失败
// }

void	destroy_textures(t_club *club)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (club->tex[i].img)
			mlx_destroy_image(club->mlx, club->tex[i].img);
		i++;
	}
}
