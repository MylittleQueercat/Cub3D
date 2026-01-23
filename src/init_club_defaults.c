/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_club_defaults.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilwang <lilwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:26:47 by hguo              #+#    #+#             */
/*   Updated: 2026/01/23 16:13:49 by lilwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_values_defaults(t_club *club)
{
	club->map.width = 0;
	club->map.height = 0;
	club->floor_color = 0;
	club->ceiling_color = 0;
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
}

bool	init_door_tex_defaults(t_club *club)
{
	if (!is_valid_xpm_file("xpms/door2.xpm"))
	{
		err_msg("Error: Door XPM file not found or invalid");
		return (false);
	}
	ft_bzero(&club->door_tex, sizeof(t_tex));
	club->door_tex.path = ft_strdup("xpms/door2.xpm");
	ft_bzero(&club->door_open_tex, sizeof(t_tex));
	club->door_open_tex.path = ft_strdup("xpms/door2.xpm");
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
