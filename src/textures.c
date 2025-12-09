#include "../include/cub3d.h"

static int	load_texture(t_club *club, t_tex *tex, char *path)
{
	//读取.xpm文件，在内存里建图
	tex->img = mlx_xpm_file_to_image(club->mlx,
			path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	//从图里拿到底层像素数据的地址
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

int	load_all_textures(t_club *club)
{
	if (load_texture(club, &club->tex[TEX_NO], "textures/no.xpm"))
		return (1);
	if (load_texture(club, &club->tex[TEX_SO], "textures/so.xpm"))
		return (1);
	if (load_texture(club, &club->tex[TEX_WE], "textures/we.xpm"))
		return (1);
	if (load_texture(club, &club->tex[TEX_EA], "textures/ea.xpm"))
		return (1);
	if (load_texture(club, &club->tex[TEX_CEIL], "textures/floor1.xpm"))
		return (1);
	if (load_texture(club, &club->tex[TEX_FLOOR], "textures/floor3.xpm"))
		return (1);
	return (0);
}

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

