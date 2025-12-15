#include "../include/cub3d.h"
#include <stdio.h>

int	close_window(t_club *club)
{
    destroy_textures(club);
	destroy_image(club);

	if (club->win)
		mlx_destroy_window(club->mlx, club->win);
	exit(0);
	return (0);
}

int key_hook(int keycode, t_club *club)
{
    double move_speed = 0.1;
    double rot_speed = 0.09;

    if (keycode == KEY_ESC)
        close_window(club);
    else if (keycode == KEY_W)
        move_forward_backward(club, move_speed);
    else if (keycode == KEY_S)
        move_forward_backward(club, -move_speed);
    else if (keycode == KEY_A)
        strafe_left_right(club, +move_speed);
    else if (keycode == KEY_D)
        strafe_left_right(club, -move_speed);
    else if (keycode == KEY_LEFT)
        rotate_player(club, +rot_speed);
    else if (keycode == KEY_RIGHT)
        rotate_player(club, -rot_speed);
	else if (keycode == KEY_O)
		try_open_door(club);
    return (0);
}
