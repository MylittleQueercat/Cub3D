/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_club_defaults.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilwang <lilwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:26:47 by hguo              #+#    #+#             */
/*   Updated: 2026/01/26 14:13:45 by lilwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_values_defaults(t_club *club)
{
	club->sprite_count = 0;
	club->sprite_jump = 0;
	club->found_count = 0;
	club->game_won = 0;
	club->win_loaded = 0;
	club->door_count = 0;
	club->mouse_last_x = WIDTH / 2;
	club->mouse_in_window = 0;
	club->show_minimap = 1;
	club->mouse_left = 0;
	club->mouse_sens = 0.003;
	club->key_w = 0;
	club->key_a = 0;
	club->key_s = 0;
	club->key_d = 0;
	club->key_left = 0;
	club->key_right = 0;
	club->ceiling_color = -1;
	club->floor_color = -1;
}

bool	init_door_tex_defaults(t_club *club)
{
	if (!is_valid_xpm_file("xpms/door2.xpm"))
		return (err_msg("Error: Door XPM file not found or invalid"), false);
	ft_bzero(&club->door_tex, sizeof(t_tex));
	club->door_tex.path = ft_strdup("xpms/door2.xpm");
	club->door_tex.img = mlx_xpm_file_to_image(club->mlx, club->door_tex.path,
			&club->door_tex.width, &club->door_tex.height);
	if (!club->door_tex.img)
		return (err_msg("Error: Failed to load door image via MLX"), false);
	club->door_tex.addr = mlx_get_data_addr(club->door_tex.img,
			&club->door_tex.bpp, &club->door_tex.line_len,
			&club->door_tex.endian);
	if (!club->door_tex.addr)
		return (err_msg("Error: Failed to get door data address"), false);
	club->door_open_tex = club->door_tex;
	return (true);
}

static void	init_tex_arrays_defaults(t_club *club)
{
	ft_bzero(club->tex, sizeof(club->tex));
	ft_bzero(club->sprite_textures, sizeof(club->sprite_textures));
}

int	init_club_defaults(t_club *club)
{
	init_values_defaults(club);
	init_tex_arrays_defaults(club);
	return (0);
}
