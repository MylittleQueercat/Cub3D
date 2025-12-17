#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

// 窗口大小
# define WIDTH 1200
# define HEIGHT 1000

/* Key definitions for Mac and Linux compatibility */
#ifdef __APPLE__
    #define KEY_ESC    53
    #define KEY_W      13
    #define KEY_S      1
    #define KEY_A      0
    #define KEY_D      2
    #define KEY_Q      12
    #define KEY_E      14
    #define KEY_LEFT   123
    #define KEY_RIGHT  124
    #define KEY_O      31
    #define KEY_MAP    46
#elif __linux__
    #define KEY_ESC    65307
    #define KEY_W      119
    #define KEY_S      115
    #define KEY_A      97
    #define KEY_D      100
    #define KEY_Q      113
    #define KEY_E      101
    #define KEY_LEFT   65361
    #define KEY_RIGHT  65363
    #define KEY_O      111
    #define KEY_MAP    109
#endif

//纹理结构
# define TEX_NO		0 //北
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3
// # define TEX_COUNT	4
# define TEX_CEIL   4
# define TEX_FLOOR  5
# define TEX_COUNT	6 //墙的面数
// # define KEY_MAP    46

#define FOV 0.66

//颜色
#define MM_BG       0x2A003A   // 深紫色
#define MM_WALL     0xFF6ADE   // 亮粉色
#define MM_PLAYER   0xFFC1F5   // 淡粉
#define MM_DOOR     0xAA55FF   // 紫色

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
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
	int		width;
	int		height;
}   t_img;

//map
typedef struct	s_map {
	char	**grid;
	int		width;
	int		height;
	int		map_end_index;
}	t_map;

//player
typedef struct s_player {
	char	pos;
	double	x;
	double	y;
	double	dir_x; //玩家朝
					// 计算纹理坐标向
	double	dir_y;
	double	plane_x; //摄像机平面
	double	plane_y;
}	t_player;


typedef struct	s_door
{
	double	x;
	double	y;
	bool	is_open;
	t_img	img_closed;
	t_img	img_open;
	bool	visible;
	double	screen_x;
	int		width;
	int		height;
	double	perp_dist;
}	t_door;

typedef struct s_sprite
{
	double	x;
	double	y;
	bool	visible;
	int		distance;
	//t_img	img;
	int		screen_x;
	int		width;
	int		height;
	double	sprite_angle;
	int		color;
}	t_sprite;

typedef enum e_hit
{
	HIT_NONE,
	HIT_WALL,
	HIT_DOOR
}	t_hit;

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
	t_hit	hit_type;
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
    t_img       img;            // 当前帧画布
    t_map       map;            // 地图数据
    t_player    player;         // 玩家状态
	t_sprite	*sprites;
	t_img		sprite_texture;
	int			sprite_count;
	t_door		*doors;
	int			door_count;
    t_tex       tex[TEX_COUNT]; // 0:N, 1:S, 2:W, 3:E
    int         floor_color;    // F
    int         ceiling_color;  // C
	int         mouse_last_x;       // 上一次鼠标
    int         mouse_in_window;    // 鼠标刚进窗口
    int         show_minimap;
    int         mouse_left;         //鼠标左键
    double      mouse_sens;         //鼠标灵敏度
	double		z_buffer[WIDTH]; //屏幕第 x 列最近的墙到玩家的距离
}   t_club;

//parsing
bool	is_valid_xpm_file(char *path);
bool	is_valid_map_line(char *line);
int		check_elements(t_club *club, char **lines);
int		get_map(t_club *club, char **file);
int 	parse_color(char *line, t_club *club);
int		parse_texture(char *line, t_club *club);
int		parse_texture(char *line, t_club *club);
bool	prepare_map(t_club *club);
bool	find_sprite_position(t_club *club);
bool	find_door_position(t_club *club);
bool	is_cub_file(char *arg);
char	**read_file(const char *file);
int		parsing(t_club *club, char **file);
bool	check_map_valid(t_club *club);
bool	is_empty_line(char *line);
bool	is_map_at_the_end(t_club *club, char **file);

// hooks.c
int		close_window(t_club *club);
int		key_hook(int keycode, t_club *club);

// img_utils.c
void    init_club_defaults(t_club *club);
int		init_image(t_club *club);
void	destroy_image(t_club *club);
void	put_pixel(t_img *img, int x, int y, int color);

// init_club.c
int		init_club(t_club *club);

// render_background.c
void	render_background(t_club *club);

// raycast.c
int 	is_wall(t_club *club, int map_x, int map_y);
void    draw_wall_stripe(t_club *club, int x, t_ray *ray);

// render_walls.c
void	draw_wall(t_club *club, int x, t_ray *ray);
void    render_walls(t_club *club);

// move.c
void    move_forward_backward(t_club *club, double move_speed);
void    strafe_left_right(t_club *club, double move_speed);
void    rotate_player(t_club *club, double rot_speed);

// textures.c
int		load_all_textures(t_club *club);
void	destroy_textures(t_club *club);

//sprites
int		count_char_in_map(char **map, char target);
bool	init_sprits(t_club *club);
void	render_sprites(t_club *club, t_img *img);
bool	init_doors(t_club *club);
void	try_open_door(t_club *club);
int		load_sprites(t_club *club);
int		load_door_textures(t_club *club);
void	render_doors(t_club *club);

//utils.c
void	err_msg(char *msg);
void	free_array(char **arr);

// render_minimap_bonus.c
void    render_minimap(t_club *club);

// mouse_bonus.c
int     mouse_press(int button, int x, int y, t_club *club);
int     mouse_release(int button, int x, int y, t_club *club);
int     mouse_move(int x, int y, t_club *club);

#endif