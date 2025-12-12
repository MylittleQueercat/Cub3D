#include "../include/cub3d.h"

int mouse_press(int button, int x, int y, t_club *club)
{
    (void)x;
    (void)y;
    if (button == 1)              // 左键
        club->mouse_left = 1;
    return (0);
}

int mouse_release(int button, int x, int y, t_club *club)
{
    (void)x;
    (void)y;
    if (button == 1)
        club->mouse_left = 0;
    return (0);
}

int mouse_move(int x, int y, t_club *club)
{
    (void)y; //无需处理上下视角
	int	dx;
    if (!club->mouse_left)
    {
        club->mouse_in_window = 0;
        return (0);
    }	
    if (x < 0 || x >= WIDTH)
    {
        club->mouse_in_window = 0;
        return (0);
    }
    if (!club->mouse_in_window)
    {
        club->mouse_last_x = x;
        club->mouse_in_window = 1;
        return (0);
    }
    dx = x - club->mouse_last_x;
    if (dx == 0)
        return (0);
    double rot_speed = dx * club->mouse_sens;
    rotate_player(club, -rot_speed);
    club->mouse_last_x = x;
    return (0);
}
