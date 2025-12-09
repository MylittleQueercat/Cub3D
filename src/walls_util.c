#include "../include/cub3d.h"

// 根据射线的方向和碰撞的面，选择 NO / SO / WE / EA
static int  choose_texture(t_ray *r)
{
    if (r->side == 0) // 撞到 x 方向
    {
        if (r->ray_dir_x > 0)
            return (TEX_WE); // 往 +x 看
        else
            return (TEX_EA); // 往 -x 看
    }
    else // 撞到 y 方向
    {
        if (r->ray_dir_y > 0)
            return (TEX_NO); // 往 +y 看
        else
            return (TEX_SO); // 往 -y 看
    }
}

void    draw_wall_stripe(t_club *club, int x, t_ray *r)
{
    int     tex_id;
    t_tex   *tex;
    double  wall_x;
    int     tex_x;
    double  step;
    double  tex_pos;
    int     y;

    // 1. 选纹理
    tex_id = choose_texture(r);
    tex = &club->tex[tex_id];

    // 2. 计算墙上的命中位置：wall_x ∈ [0, 1)
    if (r->side == 0)
        wall_x = club->player.y + r->perp_wall_dist * r->ray_dir_y;
    else
        wall_x = club->player.x + r->perp_wall_dist * r->ray_dir_x;
    wall_x -= floor(wall_x);

    // 3. 算纹理 x 坐标
    tex_x = (int)(wall_x * (double)tex->width);
    if (r->side == 0 && r->ray_dir_x > 0)
        tex_x = tex->width - tex_x - 1;
    if (r->side == 1 && r->ray_dir_y < 0)
        tex_x = tex->width - tex_x - 1;

    // 4. y 方向步长：屏幕每向下走 1 像素，纹理走多少
    step = 1.0 * tex->height / r->line_height;
    tex_pos = (r->draw_start - HEIGHT / 2 + r->line_height / 2) * step;

    // 5. 逐行从纹理采样，画到屏幕
    y = r->draw_start;
    while (y < r->draw_end)
    {
        int     tex_y;
        char    *pixel;
        int     color;

        tex_y = (int)tex_pos;
        if (tex_y < 0)
            tex_y = 0;
        if (tex_y >= tex->height)
            tex_y = tex->height - 1;
        tex_pos += step;

        pixel = tex->addr
            + tex_y * tex->line_len
            + tex_x * (tex->bpp / 8);
        color = *(int *)pixel;
        put_pixel(&club->img, x, y, color);
        y++;
    }
}

// 判断某个格子是不是墙
int is_wall(t_club *club, int map_x, int map_y)
{
    if (map_x < 0 || map_x >= club->map.width
        || map_y < 0 || map_y >= club->map.height)
        return (1);
    return (club->map.grid[map_y][map_x] == '1');
}
