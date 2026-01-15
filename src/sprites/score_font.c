#include "../include/cub3d.h"

static const unsigned char g_font_s[7] = {0b01110,0b10001,0b10000,0b01110,0b00001,0b10001,0b01110};
static const unsigned char g_font_c[7] = {0b01110,0b10001,0b10000,0b10000,0b10000,0b10001,0b01110};
static const unsigned char g_font_o[7] = {0b01110,0b10001,0b10001,0b10001,0b10001,0b10001,0b01110};
static const unsigned char g_font_r[7] = {0b11110,0b10001,0b10001,0b11110,0b10100,0b10010,0b10001};
static const unsigned char g_font_e[7] = {0b11111,0b10000,0b10000,0b11110,0b10000,0b10000,0b11111};

static void	draw_glyph5x7(t_img *img, int x, int y,
	const unsigned char *g, int color, int scale)
{
	int	r;
	int	c;
	int	px;
	int	py;

	r = 0;
	while (r < 7)
	{
		c = 0;
		while (c < 5)
		{
			if (g[r] & (1 << (4 - c)))
			{
				py = 0;
				while (py < scale)
				{
					px = 0;
					while (px < scale)
					{
						put_pixel(img, x + c * scale + px,
							y + r * scale + py, color);
						px++;
					}
					py++;
				}
			}
			c++;
		}
		r++;
	}
}

static int	score_step(int scale)
{
	return ((5 * scale) + (2 * scale));
}

void	ui_draw_text_score(t_img *img, int x, int y, int color, int scale)
{
	int	step;

	step = score_step(scale);
	draw_glyph5x7(img, x + step * 0, y, g_font_s, color, scale);
	draw_glyph5x7(img, x + step * 1, y, g_font_c, color, scale);
	draw_glyph5x7(img, x + step * 2, y, g_font_o, color, scale);
	draw_glyph5x7(img, x + step * 3, y, g_font_r, color, scale);
	draw_glyph5x7(img, x + step * 4, y, g_font_e, color, scale);
}

int	ui_score_label_width(int scale)
{
	return (score_step(scale) * 5);
}
