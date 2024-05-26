/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:07:23 by aberion           #+#    #+#             */
/*   Updated: 2024/05/20 14:57:51 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "ft_printf/src/ft_printf.h"
#include "minilibx-linux/mlx.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

int close_window(void *param)
{
    t_mlx *mlx = (t_mlx *)param;
    
    if (mlx && mlx->mlx_p && mlx->win_p)
    {
        mlx_clear_window(mlx->mlx_p, mlx->win_p);
        mlx_destroy_window(mlx->mlx_p, mlx->win_p);
        mlx_destroy_display(mlx->mlx_p);
    }
    free(mlx->mlx_p);
    free(mlx);
    exit(0);
    return (0);
}

void move_player(t_game *game, int move_x, int move_y)
{
    int new_x = game->info->x + move_x;
    int new_y = game->info->y + move_y;
    int gang = 0;
    char target_tile;   

    if (new_x >= 0 && new_x < game->map->rows && new_y >= 0 && new_y < game->map->cols
        && game->map->map[new_x][new_y] != '1')
    {
        game->info->count_move++;
        ft_printf("%d\n", game->info->count_move);
        target_tile = game->map->map[new_x][new_y];
        if (target_tile == 'C')
            game->info->left_items--;
        if (target_tile == 'E' && game->info->left_items == 0)
            close_window(game->mlx);
        if (target_tile == 'E')
            gang++;
        if (game->map->map[game->info->x][game->info->y] != 'E')
            game->map->map[game->info->x][game->info->y] = '0';
        game->info->x = new_x;
        game->info->y = new_y;
        game->map->map[game->info->x][game->info->y] = 'P';
        mlx_clear_window(game->mlx->mlx_p, game->mlx->win_p);
        draw_map(game);
        if (gang != 0)
            game->map->map[game->info->x][game->info->y] = 'E';
    }
}

int key_press(int keycode, t_game *game)
{
    if (keycode == ESC_KEY)
        close_window(game->mlx);
    else if (keycode == KEY_UP)
        move_player(game, -1, 0);
    else if (keycode == KEY_DOWN)
        move_player(game, 1, 0);
    else if (keycode == KEY_LEFT)
        move_player(game, 0, -1);
    else if (keycode == KEY_RIGHT)
        move_player(game, 0, 1);
    return (0);
}

void draw_map(t_game *game)
{
    int i, j;
    void *grass = mlx_xpm_file_to_image(game->mlx->mlx_p, "assets/grass.xpm", &game->mlx->width, &game->mlx->height);
    void *wall = mlx_xpm_file_to_image(game->mlx->mlx_p, "assets/wall.xpm", &game->mlx->width, &game->mlx->height);
    void *coin = mlx_xpm_file_to_image(game->mlx->mlx_p, "assets/coin.xpm", &game->mlx->width, &game->mlx->height);
    void *exit = mlx_xpm_file_to_image(game->mlx->mlx_p, "assets/exit.xpm", &game->mlx->width, &game->mlx->height);
    void *chara = mlx_xpm_file_to_image(game->mlx->mlx_p, "assets/char.xpm", &game->mlx->width, &game->mlx->height);
    int offset_x = (WIN_WIDTH - (game->map->tile_width * game->map->cols)) / 2;
    int offset_y = (WIN_HEIGHT - (game->map->tile_height * game->map->rows)) / 2;

    i = 0;
    if (!grass || !wall || !coin || !exit || !chara)
    {
        perror("Error loading one or more images");
        return;
    }
    while (i < game->map->rows)
    {
        j = 0;
        while (j < game->map->cols)
        {
            if (game->map->map[i][j] == '0')
                mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p, grass, offset_x + j * game->map->tile_width, offset_y + i * game->map->tile_height);
            else if (game->map->map[i][j] == '1')
                mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p, wall, offset_x + j * game->map->tile_width, offset_y + i * game->map->tile_height);
            else if (game->map->map[i][j] == 'C')
                mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p, coin, offset_x + j * game->map->tile_width, offset_y + i * game->map->tile_height);
            else if (game->map->map[i][j] == 'E')
                mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p, exit, offset_x + j * game->map->tile_width, offset_y + i * game->map->tile_height);
            else if (game->map->map[i][j] == 'P')
                mlx_put_image_to_window(game->mlx->mlx_p, game->mlx->win_p, chara, offset_x + j * game->map->tile_width, offset_y + i * game->map->tile_height);
            j++;
        }
        i++;
    }
    mlx_destroy_image(game->mlx->mlx_p, grass);
    mlx_destroy_image(game->mlx->mlx_p, wall);
    mlx_destroy_image(game->mlx->mlx_p, coin);
    mlx_destroy_image(game->mlx->mlx_p, exit);
    mlx_destroy_image(game->mlx->mlx_p, chara);
}

void init_info(t_game *game)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    game->info->left_items = 0;
    game->info->count_move = 0;
    while (i < game->map->rows)
    {
        j = 0;
        while (j < game->map->cols)
        {
            if (game->map->map[i][j] == 'C')
                game->info->left_items++;
            if (game->map->map[i][j] == 'P')
            {
                game->info->x = i;
                game->info->y = j;
            }
            j++;
        }
        i++;
    }
    game->map->tile_width = WIN_WIDTH / game->map->cols;
    game->map->tile_height = WIN_HEIGHT / game->map->rows;
    game->mlx->width = 0;
    game->mlx->height = 0;

}

int main(int argc, char **argv)
{
    t_game *game;

    if (argc < 2)
    {
        perror("Error, please add a map file");
        return 1;
    }
    if (check_map(argv) != 0)
        return 1;
    game = (t_game *)malloc(sizeof(t_game));
    if (!game)
    {
        perror("Error allocating memory for game");
        return 1;
    }
    game->map = (t_map *)malloc(sizeof(t_map));
    if (!game->map)
    {
        free(game);
        perror("Error allocating memory for map");
        return 1;
    }
    game->info = (t_info *)malloc(sizeof(t_info));
    if (!game->info)
    {
        free(game);
        perror("Error allocating memory for info");
        return 1;
    }
    if (init_map(argv, game->map) != 0)
        return 1;
    game->mlx = (t_mlx *)malloc(sizeof(t_mlx));
    if (!game ->mlx)
        return (1);
    game->mlx->mlx_p = mlx_init(); // Initialiser la bibliothèque graphique
    if (!game->mlx->mlx_p)
    {
        free(game->mlx);
        return (1); 
    }
    init_info(game);
    
    game->mlx->win_p = mlx_new_window(game->mlx->mlx_p, 800, 600, "First window MiniLibX"); // Créer une nouvelle fenêtre
    if (!game->mlx->win_p)
    {
        free(game->mlx);
        return (1); // Gestion d'erreur si mlx_new_window échoue
    }
    
    draw_map(game);

    mlx_hook(game->mlx->win_p, 17, 0, close_window, game);
    mlx_key_hook(game->mlx->win_p, key_press, game);
    mlx_loop(game->mlx->mlx_p);
    return (0);
}
