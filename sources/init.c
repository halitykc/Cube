#include "../includes/cube3d.h"

void	init_player(t_player *player, t_game *game) //
{
	player->x = WIDTH/2;
	player->y = HEIGHT/2;
	player->rotation = P/2;

	player->key_down = 0;
	player->key_right = 0;
	player->key_up = 0;
	player->key_left = 0;

	player->rotate_left = 0;
	player->rotate_right = 0;
    player->game = game;
}

void	init_game(t_game *game)
{
	init_player(&game->player, game);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "G");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

#input.c
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
#main.c

#include "../includes/cube3d.h"

int		key_esc(int keycode, t_game	*game)
{

	if (keycode == XK_Escape)
		exitt(game);
    printf("GİRDİ\n");
    return 0;
}


void    key_hooks(t_game *game)
{

    mlx_hook(game->win, KeyPress, 1L<<0, key_press, &game->player);
	mlx_hook(game->win, KeyRelease, 1L<<1, key_release, &game->player);
    mlx_hook(game->win, DestroyNotify, StructureNotifyMask, exitt, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
}



int	main(void)
{

	t_game	game;
	init_game(&game);
    key_hooks(&game);
	mlx_loop(game.mlx);

	return (0);
}