/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:21:59 by hyakici           #+#    #+#             */
/*   Updated: 2025/11/22 13:24:55 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	offset;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	offset = (y * game->size_line) + (x * (game->bpp / 8));
	*(unsigned int *)(offset + game->data) = color;
}

void	clear_image(t_game *game)
{
	memset(game->data, 0, game->size_line * HEIGHT);
}

char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "000111111111111";
	map[1] = "011111100000001";
	map[2] = "110000000000001";
	map[3] = "100000100000001";
	map[4] = "100000000000001";
	map[5] = "100000010000001";
	map[6] = "100000000000001";
	map[7] = "100000000000001";
	map[8] = "100000000000001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}