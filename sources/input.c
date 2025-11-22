/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:01:58 by hyakici           #+#    #+#             */
/*   Updated: 2025/11/22 13:02:08 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	exitt(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		free(game->map);
	}
	exit(0);
	return (31);
}

int	key_press(int keycode, t_player	*player)
{
	printf("x : %f \n", player->x);
	printf("y : %f \n", player->y);
	if (keycode == XK_s)
		player->key_up = 1;
	if (keycode == XK_w)
		player->key_down = 1;
	if (keycode == XK_a)
		player->key_right = 1;
	if (keycode == XK_d)
		player->key_left = 1;
	if (keycode == XK_Left)
		player->rotate_left = 1;
	if (keycode == XK_Right)
		player->rotate_right = 1;
	if (keycode == XK_Escape)
		exitt(player->game);
	return (0);
}

int	key_release(int keycode, t_player	*player)
{
	if (keycode == XK_s)
		player->key_up = 0;
	if (keycode == XK_w)
		player->key_down = 0;
	if (keycode == XK_a)
		player->key_right = 0;
	if (keycode == XK_d)
		player->key_left = 0;
	if (keycode == XK_Left)
		player->rotate_left = 0;
	if (keycode == XK_Right)
		player->rotate_right = 0;
	return (0);
}
