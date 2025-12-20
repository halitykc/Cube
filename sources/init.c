/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:06:41 by hyakici           #+#    #+#             */
/*   Updated: 2025/12/20 12:02:11 by hyakici          ###   ########.fr       */
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
	player->speed = 3;
	player->angle_speed = P / 56;
}

void	aq_oc_fonksiyonu(t_game *game, int *h, int *w)
{
	game->north_wall.img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", w, h);
	game->north_wall.addr = mlx_get_data_addr(game->north_wall.img, &game->north_wall.bpp, &game->north_wall.row_length, &game->north_wall.endian);
	game->north_wall.width = *w;
	game->north_wall.height = *h;
	game->west_wall.img = mlx_xpm_file_to_image(game->mlx, "./textures/west_wall.xpm", w, h);
	game->west_wall.addr = mlx_get_data_addr(game->west_wall.img, &game->west_wall.bpp, &game->west_wall.row_length, &game->west_wall.endian);
	game->west_wall.width = *w;
	game->west_wall.height = *h;
	game->south_wall.img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", w, h);
	game->south_wall.addr = mlx_get_data_addr(game->south_wall.img, &game->south_wall.bpp, &game->south_wall.row_length, &game->south_wall.endian);
	game->south_wall.width = *w;
	game->south_wall.height = *h;
	game->east_wall.img = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm", w, h);
	game->east_wall.addr = mlx_get_data_addr(game->east_wall.img, &game->east_wall.bpp, &game->east_wall.row_length, &game->east_wall.endian);
	game->east_wall.width = *w;
	game->east_wall.height = *h;
}

void	init_game(t_game *game)
{
	int	h;
	int	w;

	init_player(&game->player, game);
	game->map = get_map();
	game->mlx = mlx_init();
	aq_oc_fonksiyonu(game, &h, &w);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cube");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
