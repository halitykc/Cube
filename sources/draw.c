#include "../includes/cube3d.h"

void	put_pixel(int x, int y ,int color, t_game *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;
	int	offset;

	offset = (y * game->size_line) + (x * (game->bpp / 8));
	*(unsigned int *)(offset + game->data) = color;
}

// void	draw_square(int x, int y, int size, int color, t_game *game)
// {
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x  + i, y, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x, y + i, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x + size, y + i, color, game);
// 	for (int i = 0; i < size; i++)
// 		put_pixel(x + i, y + size, color, game);
// }

char	**get_map(void)
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = "   111111111111";
    map[1] = "   111100000001";
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

// void	draw_map(t_game *game)
// {
// 	char **map = game->map;
// 	int color = 0x0000FF;
// 	for (int y = 0; map[y]; y++)
// 		for (int x = 0; map[y][x]; x++)
// 			if (map[y][x] == '1')
// 				draw_square(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE,color, game);
// }


int throw_ray(float x, float y, t_game *game)
{
	int xx;
	int yx;

	xx= (int)(x / BLOCK_SIZE); // ray duvarada değiyor mu değiyorsa 1
	yx= (int)(y / BLOCK_SIZE);
	// harita dışı durumları duvar say
	if (xx < 0 || yx < 0)
		return 1;
	if (!game->map[yx])
		return 1;
	if (xx >= (int)strlen(game->map[yx]))
		return 1;
	if (game->map[yx][xx] == '1')
		return 1;
	return 0;
}

float cast_single_ray(float ray_angle, t_game *g, t_player *p)
{
    float x;
	float y;
    float step_len;
	float cx;
	float sx;
    int steps;

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
			break;
    }
    float dx;
	float dy;
	dx = x - p->x;
	dy = y - p->y;
    return sqrtf(dx*dx + dy*dy);
}

void draw_vline(int x, int y0, int y1, int color, t_game *g)
{
    if (x < 0 || x >= WIDTH)
		return;
    if (y0 < 0)
		y0 = 0;
    if (y1 >= HEIGHT)
		y1 = HEIGHT - 1;
	
    for (int y = y0; y <= y1; y++)
        put_pixel(x, y, color, g);
}


/* int draw_loop(t_game *game)  
 {
 	t_player *player = &game->player;
 	move_player(player, game);
 	clear_image(game);
 	draw_square(player->x, player->y, 50, 0x00FF00, game);
 	draw_map(game);
 	// Işın parametreleri
 	float	start_angle = player->rotation - (60 * (P / 180)) / 2 ;
 	float	step = (60 * (P / 180)) / NUM_RAYS;
 	int i = -1;
 	while (++i < NUM_RAYS)
 	{
 		float xray = player->x;
 		float yray = player->y;
 		float ray_angle = start_angle + (i * step);
 		float cos_a = -cos(ray_angle);
 		float sin_a = -sin(ray_angle);
 		int steps = 0;
 		while (!throw_ray(xray, yray, game) && steps++ < MAX_STEPS)
 		{
 			if ((int)xray >= 0 && (int)xray < WIDTH && (int)yray >= 0 && (int)yray < HEIGHT)
 				put_pixel((int)xray, (int)yray, 0xFF0000, game);
 			xray += cos_a * 1.5f;
 			yray += sin_a * 1.5f;
 			if (xray < 0 || xray >= WIDTH || yray < 0 || yray >= HEIGHT)
 				break;
 		}
 	}
 	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
 	return 0;
 }
*/

int draw_loop(t_game *game)
{
	move_player(&game->player, game);
	clear_image(game);
	
	float proj_plane = (WIDTH / 2) / tanf((60 * (P / 180)) / 2.0);
	float start_angle = game->player.rotation - (60 * (P / 180)) / 2.0;
	float step = (60 * (P / 180)) / (float)WIDTH;

	int col;
	col = -1;
	while (++col < WIDTH)
	{
		float ray_angle = start_angle + col * step;
		float dist = cast_single_ray(ray_angle, game, &game->player);
		dist *= cosf(ray_angle - game->player.rotation); // Fisheye düzeltmesi

		if (dist < 1)
			dist = 1;
		float wall_height = (BLOCK_SIZE * proj_plane) / dist;

		int top = (HEIGHT / 2) - (wall_height / 2);
		int bottom = (HEIGHT / 2) + (wall_height / 2);

		draw_vline(col, 0, top, 0x87CEEB, game);
		draw_vline(col, top, bottom, 0x888888, game);
		draw_vline(col, bottom, HEIGHT, 0x444444, game);
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}
void clear_image(t_game *game)
{
    for(int y = 0; y < HEIGHT; y++)
        for(int x = 0; x < WIDTH; x++)
            put_pixel(x, y, 0, game);
}
