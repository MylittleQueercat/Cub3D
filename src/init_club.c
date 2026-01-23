/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_club.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilwang <lilwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:27:04 by hguo              #+#    #+#             */
/*   Updated: 2026/01/23 14:01:04 by lilwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_club(t_club *club)
{
	club->mlx = mlx_init();
	if (!club->mlx)
		return (1);
	club->win = mlx_new_window(club->mlx, WIDTH, HEIGHT, "PINK PONY CLUB");
	if (!club->win)
		return (1);
	if (load_win_banner(club))
		return (err_msg("failed to load win banner"), 1);
	if (init_image(club))
		return (1);
	if (!init_doors(club))
		return (1);
	if (!init_sprits(club))
		return (1);
	return (0);
}
