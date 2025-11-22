/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:06:41 by hyakici           #+#    #+#             */
/*   Updated: 2025/11/22 13:28:18 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	init_player(t_player *player, t_game *game)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->rotation = P / 2;
	player->key_down = 0;
	player->key_right = 0;
	player->key_up = 0;
	player->key_left = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
	player->game = game;
	player->speed = 1;
	player->angle_speed = 0.05;
}

void	init_game(t_game *game)
{
	init_player(&game->player, game);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "G");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
