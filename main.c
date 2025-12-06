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

	if (argc != 2)
		return (err_msg("Usage: ./cub3d <map.cub>"), 1);
	if (!is_cub_file(argv[1]))
		return (err_msg("Error: invalid .cun file"), 1);
	if (parsing(&club, read_file(argv[1])) == -1)
		return (err_msg("Error: parsing failed"), 1);
	if (init_club(&club))
		return (1);
	mlx_hook(club.win, 17, 0, close_window, &club);
	mlx_key_hook(club.win, key_hook, &club);
	mlx_loop_hook(club.mlx, render_loop, &club);
	mlx_loop(club.mlx);
	return (0);
}
	