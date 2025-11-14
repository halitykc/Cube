#include "../includes/cube3d.h"


void	move_player(t_player *player, t_game *game)
{
	int speed= 3;
	float angle_speed = 0.05;
	if (player->rotate_left)
		player->rotation -= angle_speed;
	if (player->rotate_right)
		player->rotation += angle_speed;
	if (player->rotation > 2 * P)
		player->rotation -= 2 * P;
	if (player->rotation < 0)
		player->rotation += 2 * P;
	float cos_angle = cos(player->rotation);
	float sin_angle = sin(player->rotation);
	double new_x = player->x;
	double new_y = player->y;

	if (player->key_right)
	{
		new_y -= cos_angle * speed;
		new_x += sin_angle * speed;
	}
	if (player->key_left)
	{
		new_y += cos_angle * speed;
		new_x -= sin_angle * speed;
	}
	if (player->key_up)
	{
		new_x -= cos_angle * speed;
		new_y -= sin_angle * speed;
	}
	if (player->key_down)
	{
		new_x += cos_angle * speed;
		new_y += sin_angle * speed;
	}
	int map_x = (int)(new_x / BLOCK_SIZE);
	int map_y = (int)(new_y / BLOCK_SIZE);

	if (game->map[map_y][map_x] == '1')
		return;
	player->x = new_x;
	player->y = new_y;

}
