#include "../include/cub3d.h"

// 尝试运行
int	render_loop(t_club *club)
{
	render_background(club);
	render_walls(club);
	render_minimap(club);
	mlx_put_image_to_window(club->mlx, club->win, club->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_club	club;

	(void)argc;
	(void)argv;
	if (init_club(&club))
		return (1);
	mlx_hook(club.win, 17, 0, close_window, &club);
	mlx_key_hook(club.win, key_hook, &club);
	mlx_loop_hook(club.mlx, render_loop, &club);
	mlx_loop(club.mlx);
	return (0);
}