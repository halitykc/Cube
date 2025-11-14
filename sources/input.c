#include "../includes/cube3d.h"

int exitt(t_game *game)
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
}

int		key_press(int keycode, t_player	*player)
{
	printf("x : %f \n", player->x);
	printf("y : %f \n", player->y);

	if (keycode == W)
		player->key_up = 1;
	if (keycode == S)
		player->key_down= 1;
	if (keycode == D)
		player->key_right = 1;
	if (keycode == A)
		player->key_left = 1;
	if(keycode == R_left)
		player->rotate_left = 1;
    if(keycode == R_right)
		player->rotate_right = 1;
	if (keycode == XK_Escape)
		exitt(player->game);
	return 0;
}
int		key_release(int keycode, t_player	*player)
{
	if (keycode == W)
		player->key_up = 0;
	if (keycode == S)
		player->key_down= 0;
	if (keycode == D)
		player->key_right = 0;
	if (keycode == A)
		player->key_left = 0;
	if(keycode == R_left)
		player->rotate_left = 0;
    if(keycode == R_right)
		player->rotate_right = 0;
	return 0;
}