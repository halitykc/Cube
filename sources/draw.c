/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:10:57 by hyakici           #+#    #+#             */
/*   Updated: 2025/11/22 12:51:51 by hyakici          ###   ########.fr       */
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

int	throw_ray(float x, float y, t_game *game)
{
	int	xx;
	int	yx;

	xx = (int)(x / BLOCK_SIZE);
	yx = (int)(y / BLOCK_SIZE);
	if (xx < 0 || yx < 0)
		return (1);
	if (!game->map[yx])
		return (1);
	if (xx >= (int)strlen(game->map[yx]))
		return (1);
	if (game->map[yx][xx] == '1')
		return (1);
	return (0);
}

float	cast_single_ray(float ray_angle, t_game *g, t_player *p)
{
	float	x;
	float	y;
	float	step_len;
	float	cx;
	float	sx;
	int		steps;
	float 	dx;
	float 	dy;

	x = p->x;
	y = p->y;
	step_len = 1;
	cx = cosf(ray_angle);
	sx = sinf(ray_angle);
	steps = 0;
	while (!throw_ray(x, y, g) && steps++ < MAX_STEPS)
	{
		x += cx * step_len;
		y += sx * step_len;
		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
			break ;
	}
	dx = x - p->x;
	dy = y - p->y;
	return (sqrtf(dx*dx + dy*dy));
}

static void	draw_vline(int x, int y0, int y1, int color, t_game *g)
{
	int	y;

	y = y0;
	if (x < 0 || x >= WIDTH)
		return ;
	if (y0 < 0)
		y0 = 0;
	if (y1 >= HEIGHT)
		y1 = HEIGHT - 1;
	while (y <= y1)
	{
		put_pixel(x, y, color, g);
		y++;
	}
}

static void	draw_ray_line(t_game *game, int col, float ray_angle, float proj_plane)
{
	float	dist;
	float	wall_height;
	int		top;
	int		bottom;

	dist = cast_single_ray(ray_angle, game, &game->player);
	dist *= cosf(ray_angle - game->player.rotation);
	if (dist < 1)
		dist = 1;
	wall_height = (BLOCK_SIZE * proj_plane) / dist;
	top = (HEIGHT / 2) - (wall_height / 2);
	bottom = (HEIGHT / 2) + (wall_height / 2);
	draw_vline(col, 0, top, 0x87CEEB, game);
	draw_vline(col, top, bottom, 0x888888, game);
	draw_vline(col, bottom, HEIGHT, 0x444444, game);
}

int	draw_loop(t_game *game)
{
	float	proj_plane;
	float	start_angle;
	float	step;
	int		col;
	float	ray_angle;

	move_player(&game->player, game);
	clear_image(game);
	proj_plane = (WIDTH / 2) / tanf((60 * (P / 180)) / 2.0);
	start_angle = game->player.rotation - (60 * (P / 180)) / 2.0;
	step = (60 * (P / 180)) / (float)WIDTH;
	col = -1;
	while (++col < WIDTH)
	{
		ray_angle = start_angle + col * step;
		draw_ray_line(game, col, ray_angle, proj_plane);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
