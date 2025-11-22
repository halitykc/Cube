

#ifndef CUBE3D_H
#define CUBE3D_H

# define WIDTH 1280
# define HEIGHT 720
# define BLOCK_SIZE 64

#define NUM_RAYS 2
#define MAX_STEPS 4000

# define P 3.14

#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
#include <string.h>


typedef struct s_game t_game;

typedef struct s_player
{
    float x;
    float y;
    float rotation;

    int key_up;
    int key_down;
    int key_left;
    int key_right;

    int rotate_left;
    int rotate_right;

	int speed;
	float angle_speed;

	t_game	*game;

}   t_player;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *img;

    char *data;
    int bpp;
    int size_line;
    int endian;
    t_player player;

    char **map;
} t_game;

void	init_game(t_game *game);
int		key_release(int keycode, t_player	*player);
int		key_press(int keycode, t_player	*player);
int exitt(t_game *game);
int draw_loop(t_game *game);
char	**get_map(void);
void	move_player(t_player *player, t_game *game);
void clear_image(t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);


#endif
