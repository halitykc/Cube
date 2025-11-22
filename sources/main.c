/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 11:58:26 by hyakici           #+#    #+#             */
/*   Updated: 2025/11/22 12:01:41 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	key_esc(int keycode, t_game	*game)
{
	if (keycode == XK_Escape)
		exitt(game);
	printf("GİRDİ\n");
	return (0);
}

void	key_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, (1L << 0), key_press, &game->player);
	mlx_hook(game->win, KeyRelease, (1L << 1), key_release, &game->player);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, exitt, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	key_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
