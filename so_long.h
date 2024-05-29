/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:10:20 by aberion           #+#    #+#             */
/*   Updated: 2024/05/29 12:03:59 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf/src/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "keys.h"
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "stdbool.h"
# include <stdio.h>
# include <stdlib.h>

# define IMG_SIZE 32
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct s_counters
{
	int			checker_p;
	int			checker_e;
	int			checker_c;
}				t_counters;

typedef struct s_assets
{
	void		*grass;
	void		*wall;
	void		*coin;
	void		*exit;
	void		*chara;
}				t_assets;

typedef struct s_info
{
	int			x;
	int			y;
	int			count_move;
	int			left_items;
}				t_info;

typedef struct s_map
{
	char		**map;
	char		*name;
	int			rows;
	int			cols;
}				t_map;

typedef struct s_mlx
{
	void		*mlx_p;
	void		*win_p;
	int			width;
	int			height;
	t_assets	assets;
}				t_mlx;

typedef struct s_game
{
	t_map		*map;
	t_mlx		*mlx;
	t_info		*info;
}				t_game;

typedef struct s_map_info
{
	char		*raw_map;
	int			read_size;
	int			bytes_read;
}				t_map_info;

typedef struct s_vars
{
	int			i_2;
	int			j_2;
	int			nb_c;
}				t_vars;

int				check_map(char **argv);
void			init_map(char **argv, t_map *map);
void			draw_map(t_game *game);
char			**get_raw_map(char *map_path);
char			*ft_realloc(char *ptr, size_t size);
void			free_tab(char **tab);
void			init_info(t_game *game);
void			free_resources(t_game *game);
bool			back_tracking(char **tab_map, int x, int y, int *nb_c);
int				shall_i_pass(char **tab_map, int rows, int cols);
void			load_images(t_mlx *mlx);
int				check_and_init(int argc, char **argv, t_game **game);
int				allocate_game_resources(t_game **game_ptr);
int				key_press(int keycode, t_game *game);
int				close_window(void *param);

#endif