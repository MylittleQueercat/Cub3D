#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx/mlx.h"

// 窗口大小
# define WIDTH 800
# define HEIGHT 600

// 按键（macos系统的）
# define KEY_ESC	53
# define KEY_W      13
# define KEY_S      1
# define KEY_A      0
# define KEY_D      2
# define KEY_LEFT   123
# define KEY_RIGHT  124

//texture 墙的纹理信息
typedef struct s_tex {
	void	*img;	//mlx图片指针
	char		*addr;	//像素数据的地址, int*可以直接读写颜色
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

//club
typedef struct s_club
{
    void        *mlx;
    void        *win;
    t_img       img;            // 当前帧画布
    t_map       map;            // 地图数据
    t_player    player;         // 玩家状态
    t_tex       tex[4];         // 0:NO, 1:SO, 2:WE, 3:EA
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

// render_walls.c
int is_wall(t_club *club, int map_x, int map_y);
void render_walls(t_club *club);

// move.c
void    move_forward_backward(t_club *club, double move_speed);
void    strafe_left_right(t_club *club, double move_speed);
void    rotate_player(t_club *club, double rot_speed);

#endif