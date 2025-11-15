#include "../includes/cube3d.h"

static void	rotate_player(t_player *player)
{
	if (player->rotate_left)
		player->rotation -= player->angle_speed;
	if (player->rotate_right)
		player->rotation += player->angle_speed;
	if (player->rotation > 2 * P)
		player->rotation -= 2 * P;
	if (player->rotation < 0)
		player->rotation += 2 * P;

}

static void	position_player(t_player *player, float *new_y, float *new_x)
{
	if (player->key_right)
	{
		*new_y -= cos(player->rotation) * player->speed;
		*new_x += sin(player->rotation) * player->speed;
	}
	if (player->key_left)
	{
		*new_y += cos(player->rotation) * player->speed;
		*new_x -= sin(player->rotation) * player->speed;
	}
	if (player->key_up)
	{
		*new_x -= cos(player->rotation) * player->speed;
		*new_y -= sin(player->rotation) * player->speed;
	}
	if (player->key_down)
	{
		*new_x += cos(player->rotation) * player->speed;
		*new_y += sin(player->rotation) * player->speed;
	}
}

void	move_player(t_player *player, t_game *game)
{
	float new_x;
	float new_y;
	int map_x;
	int map_y;

	new_y = player->y;
	new_x = player->x;

	rotate_player(player);
	position_player(player, &new_y, &new_x);
	map_x = (int)(new_x / BLOCK_SIZE);
	map_y = (int)(new_y / BLOCK_SIZE);

	if (game->map[map_y][map_x] == '1')
		return;
	player->x = new_x;
	player->y = new_y;

}
