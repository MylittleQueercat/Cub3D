#include "../include/cub3d.h"

// 尝试运行
int	render_loop(t_club *club)
{
	club->sprite_jump++;
	update_doors(club);
	update_player(club);
	update_collectibles(club);
	for (int x = 0; x < WIDTH; x++)
        club->z_buffer[x] = 1e30;
	render_background(club);
	render_walls(club);
	render_sprites(club);
	if (club->show_minimap)
		render_minimap(club);
	render_score_ui(club);
	mlx_put_image_to_window(club->mlx, club->win, club->img.img, 0, 0);
	if (club->game_won)
	{
		if (club->win_img.img)
		{
			int x = (WIDTH - club->win_img.width) / 2;
			int y = (HEIGHT - club->win_img.height) / 2;
			mlx_put_image_to_window(club->mlx, club->win, club->win_img.img, x, y);
		}
		else
			mlx_string_put(club->mlx, club->win, WIDTH/2 - 40, HEIGHT/2, 0xFFFFFF, "YOU WIN!");
	}
	return (0);
}

static int	load_map(t_club *club, char *path)
{
	club->file = read_file(path);
	if (!club->file)
		return (1);
	if (parsing(club, club->file) == -1)
	{
		free_array(club->file);
		club->file = NULL;
		return (1);
	}
	return (0);
}

static int	run_game(t_club *club)
{
	if (init_club(club))
		return (err_msg("Error: init_club failed"), 1);
	if (load_all_textures(club))
		return (err_msg("Error: texture load failed"), 1);
	if (load_sprites(club))
		return (err_msg("Error: sprite load failed"), 1);
	mlx_hook(club->win, 17, 0, close_window, club);
	mlx_key_hook(club->win, key_hook, club);
	mlx_hook(club->win, 4, 1L << 2, mouse_press, club);
	mlx_hook(club->win, 5, 1L << 3, mouse_release, club);
	mlx_hook(club->win, 6, 1L << 6, mouse_move, club);
	mlx_hook(club->win, 2, 1L << 0, key_press, club);
	mlx_hook(club->win, 3, 1L << 1, key_release, club);
	mlx_loop_hook(club->mlx, render_loop, club);
	mlx_loop(club->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_club	club;

	if (argc != 2)
		return (err_msg("Usage: ./cub3d <map.cub>"), 1);
	if (!is_cub_file(argv[1]))
		return (err_msg("Error: invalid .cub file"), 1);
	ft_bzero(&club, sizeof(club));
	init_club_defaults(&club);
	if (load_map(&club, argv[1]))
		return (1);
<<<<<<< HEAD
	}
	printf ("parsing success\n"); //debug
	init_club(&club);
	if (load_all_textures(&club))
		return (err_msg("Error: texture load failed"), 1);
	if (load_sprites(&club))
		return (err_msg("Error: sprite load failed"), 1);
	// if (init_doors(&club))
    // 	return (err_msg("Error: init_doors failed"), 1);
	// if (load_door_textures(&club))
	// 	return (err_msg("Error: door load failed"), 1);
	mlx_hook(club.win, 17, 0, close_window, &club);
	mlx_key_hook(club.win, key_hook, &club);
	mlx_hook(club.win, 4, 1L << 2, mouse_press, &club);    // ButtonPress
	mlx_hook(club.win, 5, 1L << 3, mouse_release, &club); 
	mlx_hook(club.win, 6, 1L << 6, mouse_move, &club);
	mlx_hook(club.win, 2, 1L<<0, key_press, &club);     /* KeyPress */
	mlx_hook(club.win, 3, 1L<<1, key_release, &club);   /* KeyRelease */
	mlx_loop_hook(club.mlx, render_loop, &club);
	mlx_loop(club.mlx);
	// render_background(&club);
	// render_walls(&club);
	// render_minimap(&club);
	// mlx_put_image_to_window(club->mlx, club->win, club->img.img, 0, 0);
	destroy_club(&club);
	free_array(club.file);
	return (0);
=======
	return (run_game(&club));
>>>>>>> ea818b5 (sauf header)
}
