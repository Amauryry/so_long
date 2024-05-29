/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:50:20 by aberion           #+#    #+#             */
/*   Updated: 2024/05/29 11:57:15 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_moves(int *move_x, int *move_y)
{
	move_x[0] = 0;
	move_x[1] = 1;
	move_x[2] = 0;
	move_x[3] = -1;
	move_y[0] = 1;
	move_y[1] = 0;
	move_y[2] = -1;
	move_y[3] = 0;
}

bool	back_tracking(char **tab_map, int x, int y, int *nb_c)
{
	int	move_x[4];
	int	move_y[4];
	int	i;
	int	next_x;
	int	next_y;

	init_moves(move_x, move_y);
	i = 0;
	if (tab_map[x][y] == 'C' || tab_map[x][y] == 'E')
		(*nb_c)--;
	if (*nb_c == 0)
		return (true);
	tab_map[x][y] = 'V';
	while (i < 4)
	{
		next_x = x + move_x[i];
		next_y = y + move_y[i];
		if (tab_map[next_x][next_y] != 'V' && tab_map[next_x][next_y] != '1'
			&& back_tracking(tab_map, next_x, next_y, nb_c))
			return (true);
		i++;
	}
	return (false);
}

void	initialize_vars(t_vars *vars, char **tab_map, int rows, int cols)
{
	int	i;
	int	j;

	vars->nb_c = 1;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (tab_map[i][j] == 'C')
				vars->nb_c++;
			if (tab_map[i][j] == 'P')
			{
				vars->i_2 = i;
				vars->j_2 = j;
			}
			j++;
		}
		i++;
	}
}

int	shall_i_pass(char **tab_map, int rows, int cols)
{
	t_vars	vars;

	initialize_vars(&vars, tab_map, rows, cols);
	if (back_tracking(tab_map, vars.i_2, vars.j_2, &vars.nb_c) == false)
		return (0);
	return (1);
}
