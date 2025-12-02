#include "../include/cub3d.h"

// 判断某个格子是不是墙
int is_wall(t_club *club, int map_x, int map_y)
{
    if (map_x < 0 || map_x >= club->map.width
        || map_y < 0 || map_y >= club->map.height)
        return (1);
    return (club->map.grid[map_y][map_x] == '1');
}

void render_walls(t_club *club)
{
    int x = 0;

    while (x < WIDTH)
    {
        // 1. 当前屏幕列对应的“摄像机 x 坐标”（-1 ~ 1）
        double camera_x = 2.0 * x / (double)WIDTH - 1.0;

        // 2. 射线方向
        double ray_dir_x = club->player.dir_x + club->player.plane_x * camera_x;
        double ray_dir_y = club->player.dir_y + club->player.plane_y * camera_x;

        // 3. 射线起始所在的格子
        int map_x = (int)club->player.x;
        int map_y = (int)club->player.y;

        // 4. 每走一个格子在 x/y 方向上的距离增量
        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);

        // 5. 计算 step 和 初始 side_dist
        int     step_x;
        int     step_y;
        double  side_dist_x;
        double  side_dist_y;
        int     side;
        int     hit = 0;

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (club->player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - club->player.x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (club->player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - club->player.y) * delta_dist_y;
        }

        // 6. DDA：沿着射线一步步走格子，直到撞墙
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0; // 垂直面
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1; // 水平面
            }
            if (is_wall(club, map_x, map_y))
                hit = 1;
        }

        // 7. 计算到墙的垂直距离（避免鱼眼）
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = side_dist_x - delta_dist_x;
        else
            perp_wall_dist = side_dist_y - delta_dist_y;

        // 防御：避免 0 或负数
        if (perp_wall_dist < 0.0001)
            perp_wall_dist = 0.0001;

        // 8. 根据距离算墙的屏幕高度
        int line_height = (int)(HEIGHT / perp_wall_dist);

        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT)
            draw_end = HEIGHT - 1;

        // 9. 墙的颜色
        int color = 0x00FF00; // 绿
        if (side == 1)
            color = 0x0000FF; // 蓝

        // 10. 在这一列 x 上画一条竖线（只画 draw_start~draw_end）
        int y = draw_start;
        while (y <= draw_end)
        {
            put_pixel(&club->img, x, y, color);
            y++;
        }
        x++;
    }
}