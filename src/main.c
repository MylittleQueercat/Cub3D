#include "../include/cub3d.h"

// 尝试运行
// int	render_loop(t_club *club)
// {
// 	render_background(club);
// 	render_walls(club);
// 	render_minimap(club);
// 	mlx_put_image_to_window(club->mlx, club->win, club->img.img, 0, 0);
// 	return (0);
// }

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

//Debug用
static void	init_club_debug(t_club *club)
{
<<<<<<< HEAD
    int i;

    club->mlx = NULL;
    club->win = NULL;
    club->img.img = NULL;
    club->img.addr = NULL;
    club->map.grid = NULL;
    club->map.width = 0;
    club->map.height = 0;
    club->floor_color = -1;
    club->ceiling_color = -1;
	club->sprites = NULL;
	club->doors = NULL;
	club->sprite_count = 0;
	club->door_count = 0;
    i = 0;
    while (i < TEX_COUNT)
    {
        club->tex[i].img = NULL;
        club->tex[i].addr = NULL;
        club->tex[i].path = NULL;
        club->tex[i].bpp = 0;
        club->tex[i].line_len = 0;
        club->tex[i].endian = 0;
        club->tex[i].width = 0;
        club->tex[i].height = 0;
        i++;
    }
}

//parsing debug 
int	main(int argc, char **argv)
{
	t_club club;
	char	**file;

	if (argc != 2)
		return (err_msg("Usage: ./cub3d <map.cub>"), 1);
	if (!is_cub_file(argv[1]))
		return (err_msg("Error: invalid .cub file"), 1);
	init_club_debug(&club);
	file = read_file(argv[1]);
	// for (int k =0; file[k]; k++)
	// 	printf("%s", file[k]);
	if (!file)
		return (1);
	if (parsing(&club, file) == -1)
	{
		free_array(file);
		return (err_msg("Error: parsing failed"), 1);
	}
	printf("Parsing success\n");
=======
	render_background(club);
	render_walls(club);
	render_minimap(club);
	mlx_put_image_to_window(club->mlx, club->win, club->img.img, 0, 0);
>>>>>>> hguo
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	char	**file;
// 	int		k;

// 	if (argc != 2)
// 		return (err_msg("Usage: ./cub3d <map.cub>"), 1);
// 	if (!is_cub_file(argv[1]))
// 		return (err_msg("Error: invalid .cub file"), 1);
// 	file = read_file(argv[1]);
// 	if (!file)
// 		return (err_msg("Error: cannot read file"), 1);
// 	k = 0;
// 	while (file[k])
// 	{
// 		printf("%s\n", file[k]);
// 		k++;
// 	}
// 	free_array(file);
// 	printf("Parsing success\n");
// 	return (0);
// }
