#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx/mlx.h"

// 窗口大小
# define WIDTH 900
# define HEIGHT 700

// 按键（macos系统的）
# define KEY_ESC	53
# define KEY_W      13
# define KEY_S      1
# define KEY_A      0
# define KEY_D      2
# define KEY_LEFT   123
# define KEY_RIGHT  124

// // Linux Keycodes (X11)
// # define KEY_ESC    65307
// # define KEY_W      119    // 'w'
// # define KEY_S      115    // 's'
// # define KEY_A      97     // 'a'
// # define KEY_D      100    // 'd'
// # define KEY_LEFT   65361
// # define KEY_RIGHT  65363

//纹理结构
# define TEX_NO		0 //北
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3
# define TEX_CEIL   4
# define TEX_FLOOR  5
# define TEX_COUNT	6 //墙的面数

//颜色
#define MM_BG       0x2A003A   // 深紫色
#define MM_WALL     0xFF6ADE   // 亮粉色
#define MM_PLAYER   0xFFC1F5   // 淡粉

//texture 墙的纹理信息
typedef struct s_tex {
	void	*img;	//mlx图片指针
	char	*addr;	//像素数据的地址, int*可以直接读写颜色
	int		width;
	int		height;
	int		bpp;	//每个像素占多少位bit Bits Per Pixel
	int		line_len;	//一行图片像素占多少字节
	int		endian;		//大小端
	char	*path;
}	t_tex;

typedef struct s_img
{
    void    *img;
    char     *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

//map
typedef struct	s_map {
	char	**grid;
	int		width;
	int		height;
}	t_map;

//player
typedef struct s_player {
	double	x;
	double	y;
	double	dir_x; //玩家朝向
	double	dir_y;
	double	plane_x; //摄像机平面
	double	plane_y;
}	t_player;

// 纹理渲染
typedef struct s_ray
{
    double  ray_dir_x;
    double  ray_dir_y;
    int     side;
    double  perp_wall_dist;
    int     line_height;
    int     draw_start;
    int     draw_end;
}   t_ray;

// 每一格
typedef struct s_step
{
    int     map_x;
    int     map_y;
    double  delta_x;
    double  delta_y;
    double  dist_x;
    double  dist_y;
    int     step_x;
    int     step_y;
    int     side;
}   t_step;

//club
typedef struct s_club
{
    void        *mlx;
    void        *win;
    t_img       img;       // 当前帧画布
    t_map       map;            // 地图数据
    t_player    player;         // 玩家状态
    t_tex       tex[TEX_COUNT]; // 0:N, 1:S, 2:W, 3:E
    int         floor_color;    // F
    int         ceiling_color;  // C
}   t_club;

// hooks.c
int	close_window(t_club *club);
int	key_hook(int keycode, t_club *club);

// img_utils.c
int	init_image(t_club *club);
void	destroy_image(t_club *club);
void	put_pixel(t_img *img, int x, int y, int color);

// init_club.c
int	init_club(t_club *club);

// render_background.c
void	render_background(t_club *club);

// raycast.c
int 	is_wall(t_club *club, int map_x, int map_y);
void    draw_wall_stripe(t_club *club, int x, t_ray *ray);

// render_walls.c
void    render_walls(t_club *club);

// move.c
void    move_forward_backward(t_club *club, double move_speed);
void    strafe_left_right(t_club *club, double move_speed);
void    rotate_player(t_club *club, double rot_speed);

// textures.c
int		load_all_textures(t_club *club);
void	destroy_textures(t_club *club);

// render_minimap_bonus.c
void    render_minimap(t_club *club);

#endif