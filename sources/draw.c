/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyakici <hyakici@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:10:57 by hyakici           #+#    #+#             */
/*   Updated: 2025/11/22 13:24:20 by hyakici          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"


static void	draw_vline(int x, int start, int end, int color, t_game *g)
{
	int	y;

	y = -1;
	while (++y < start) // Tavan
		put_pixel(x, y, 0x87CEEB, g);
	while (y <= end && y < HEIGHT) // Duvar
	{
		put_pixel(x, y, color, g);
		y++;
	}
	while (y < HEIGHT) // Zemin
	{
		put_pixel(x, y, 0x444444, g);
		y++;
	}
}

static void	init_ray(t_ray *ray, t_game *game, float angle)
{
	ray->map_x = (int)(game->player.x / BLOCK_SIZE);
	ray->map_y = (int)(game->player.y / BLOCK_SIZE);
	ray->delta_x = fabs(1 / cosf(angle));
	ray->delta_y = fabs(1 / sinf(angle));
	if (cosf(angle) < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.x / BLOCK_SIZE - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.x / BLOCK_SIZE)
			* ray->delta_x;
	}
	if (sinf(angle) < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.y / BLOCK_SIZE - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.y / BLOCK_SIZE)
			* ray->delta_y;
	}
}

static float	get_dda_dist(t_game *game, float angle)
{
	t_ray	ray;
	int		wall_hit;

	init_ray(&ray, game, angle);
	wall_hit = 0;
	while (wall_hit == 0)
	{
		if (ray.side_x < ray.side_y)
		{
			ray.side_x += ray.delta_x;
			ray.map_x += ray.step_x;
			ray.side = 0;
		}
		else
		{
			ray.side_y += ray.delta_y;
			ray.map_y += ray.step_y;
			ray.side = 1;
		}
		if (ray.map_y < 0 || ray.map_y >= 10 || ray.map_x < 0 || ray.map_x >= 15)
			wall_hit = 1;
		else if (game->map[ray.map_y][ray.map_x] == '1')
			wall_hit = 1;
	}
	if (ray.side == 0)
		return ((ray.side_x - ray.delta_x) * BLOCK_SIZE);
	return ((ray.side_y - ray.delta_y) * BLOCK_SIZE);
}

static void	draw_one_col(t_game *game, int x, float ray_angle, float fov)
{
	float	dist;
	float	wall_height;
	int		top;
	int		bottom;

	dist = get_dda_dist(game, ray_angle);
	dist *= cosf(ray_angle - game->player.rotation);
	if (dist < 1)
		dist = 1;
	wall_height = (BLOCK_SIZE / dist) * ((WIDTH / 2) / tanf(fov / 2));
	top = (HEIGHT / 2) - (wall_height / 2);
	bottom = (HEIGHT / 2) + (wall_height / 2);
	draw_vline(x, top, bottom, 0xFFFF00, game);
}

int	draw_loop(t_game *game)
{
	int		x;
	float	fov;
	float	ray_angle;

	move_player(&game->player, game);
	clear_image(game);
	fov = 60 * (P / 180);
	x = 0;
	while (x < WIDTH)
	{
		ray_angle = game->player.rotation - (fov / 2)
			+ ((float)x / WIDTH) * fov;
		draw_one_col(game, x, ray_angle, fov);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}