#include "../include/cub3d.h"

// 尝试运行
int	render_loop(t_club *club)
{
	for (int x = 0; x < WIDTH; x++)
        club->z_buffer[x] = 1e30;
	// printf("sprite_count=%d, sprite_texture.addr=%p\n",
    //    club->sprite_count,
    //    club->sprite_texture.addr);

	render_background(club);
	render_walls(club);
	render_sprites(club, &club->img);
	//render_doors(club); 
	if (club->show_minimap)
		render_minimap(club);
	mlx_put_image_to_window(club->mlx, club->win, club->img.img, 0, 0);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	t_club	club;

// 	if (argc != 2)
// 		return (err_msg("Usage: ./cub3d <map.cub>"), 1);
// 	if (!is_cub_file(argv[1]))
// 		return (err_msg("Error: invalid .cub file"), 1);
// 	if (parsing(&club, read_file(argv[1])) == -1)
// 		return (err_msg("Error: parsing failed"), 1);
// 	if (init_club(&club))
// 		return (1);
// 	mlx_hook(club.win, 17, 0, close_window, &club);
// 	mlx_key_hook(club.win, key_hook, &club);
// 	mlx_loop_hook(club.mlx, render_loop, &club);
// 	mlx_loop(club.mlx);
// 	return (0);

// }


int	main(int argc, char **argv)
{
	t_club club;
	char	**file;

	if (argc != 2)
		return (err_msg("Usage: ./cub3d <map.cub>"), 1);
	if (!is_cub_file(argv[1]))
		return (err_msg("Error: invalid .cub file"), 1);
	init_club_defaults(&club);
	file = read_file(argv[1]);
	if (!file)
			return (1);
	if (parsing(&club, file) == -1)
	{
		printf ("parsing failed\n"); //debugprintf("sprite_count=%d, sprite_texture.addr=%p\n",
		free_array(file);
		return (1);
	}
	printf ("parsing success\n"); //debug
	init_club(&club);
	if (load_all_textures(&club))
		return (err_msg("Error: texture load failed"), 1);
	if (load_sprites(&club))
		return (err_msg("Error: sprite load failed"), 1);
	// if (load_door_textures(&club))
	// 	return (err_msg("Error: door load failed"), 1);
	mlx_hook(club.win, 17, 0, close_window, &club);
	mlx_key_hook(club.win, key_hook, &club);
	mlx_hook(club.win, 4, 1L << 2, mouse_press, &club);    // ButtonPress
	mlx_hook(club.win, 5, 1L << 3, mouse_release, &club); 
	mlx_hook(club.win, 6, 1L << 6, mouse_move, &club);
	mlx_loop_hook(club.mlx, render_loop, &club);
	mlx_loop(club.mlx);
	// render_background(&club);
	// render_walls(&club);
	// render_minimap(&club);
	// mlx_put_image_to_window(club->mlx, club->win, club->img.img, 0, 0);
	return (0);
}
