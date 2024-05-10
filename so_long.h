/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:10:20 by aberion           #+#    #+#             */
/*   Updated: 2024/05/10 17:58:40 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "ft_printf/src/ft_printf.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>



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
	int			count_mouvements;
	t_point		*dimensions;
	t_count		*info;
	int			last_mouvement;
	int			left_items;
	t_point		player;
}	t_info;

typedef struct s_map
{
	t_info	*info;
	char	**map;
	char	*name;
}	t_map;

typedef struct s_mlx
{
	void		*mlx_p;
	void		*win_p;
}	t_mlx;

typedef struct s_game
{
	t_map	*map;
	t_mlx	*mlx;
}	t_game;

int handle_key(int key, void *param);
t_game	*init_game(t_game *game, char *str);

#endif