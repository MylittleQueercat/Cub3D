#include "../include/cub3d.h"

// 前后移动 (W/S)
void move_forward_backward(t_club *club, double move_speed)
{
    double new_x = club->player.x + club->player.dir_x * move_speed;
    double new_y = club->player.y + club->player.dir_y * move_speed;

    if (!is_wall(club, (int)new_x, (int)club->player.y))
        club->player.x = new_x;
    if (!is_wall(club, (int)club->player.x, (int)new_y))
        club->player.y = new_y;
}

// 左右移动（A/D）
void strafe_left_right(t_club *club, double move_speed)
{
    double perp_x = -club->player.dir_y;
    double perp_y = club->player.dir_x;

    double new_x = club->player.x + perp_x * move_speed;
    double new_y = club->player.y + perp_y * move_speed;

    if (!is_wall(club, (int)new_x, (int)club->player.y))
        club->player.x = new_x;
    if (!is_wall(club, (int)club->player.x, (int)new_y))
        club->player.y = new_y;
}

// 左右转头（<- 和 ->）
void rotate_player(t_club *club, double rot_speed)
{
    double old_dir_x = club->player.dir_x;
    double old_plane_x = club->player.plane_x;

    club->player.dir_x = club->player.dir_x * cos(rot_speed)
        - club->player.dir_y * sin(rot_speed);
    club->player.dir_y = old_dir_x * sin(rot_speed)
        + club->player.dir_y * cos(rot_speed);

    club->player.plane_x = club->player.plane_x * cos(rot_speed)
        - club->player.plane_y * sin(rot_speed);
    club->player.plane_y = old_plane_x * sin(rot_speed)
        + club->player.plane_y * cos(rot_speed);
}
