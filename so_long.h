/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:10:20 by aberion           #+#    #+#             */
/*   Updated: 2024/05/20 14:56:44 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "ft_printf/src/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include "keys.h"

#define IMG_SIZE 32
#define WIN_WIDTH 800
#define WIN_HEIGHT 600


typedef struct s_texture
{
	void	*t_collectibles;
	void	*t_exit;
	void	*t_ground;
	void	*t_player;
	void	*t_wall;
}	t_texture;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_count
{
	int	c_collectibles;
	int	c_exit;
	int	c_ground;
	int	c_player;
	int	c_wall;
}	t_count;

typedef struct s_info
{
	int	x;
	int y;
	int			count_move;
	int			left_items;
}	t_info;

typedef struct s_map
{
	char	**map;
	char	*name;
	int	rows;
	int cols;
	int tile_width;
	int tile_height;
}	t_map;

typedef struct s_mlx
{
	void		*mlx_p;
	void		*win_p;
	int width; 
	int height;
}	t_mlx;

typedef struct s_game
{
	t_map	*map;
	t_mlx	*mlx;
	t_info *info;
}	t_game;

int check_map(char **argv);
int init_map(char **argv, t_map *map);
void draw_map(t_game *game);

#endif