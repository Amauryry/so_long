/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:20:05 by aberion           #+#    #+#             */
/*   Updated: 2024/05/27 13:53:48 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/src/ft_printf.h"
#include "so_long.h"
#include <stdio.h>

void	check_line(char *line, int cols, t_counters *counters)
{
	int	j;

	j = 0;
	while (j < cols)
	{
		if (line[j] == 'P')
			counters->checker_p++;
		if (line[j] == 'E')
			counters->checker_e++;
		if (line[j] == 'C')
			counters->checker_c++;
		j++;
	}
}

int	check_pec(char **tab_map, int rows, int cols)
{
	int			i;
	t_counters	counters;

	counters.checker_e = 0;
	counters.checker_c = 0;
	counters.checker_p = 0;
	i = 0;
	while (i < rows)
	{
		check_line(tab_map[i], cols, &counters);
		i++;
	}
	if (counters.checker_c < 1)
		return (1);
	else if (counters.checker_e != 1)
		return (1);
	else if (counters.checker_p != 1)
		return (1);
	return (0);
}

int	check_dimensions(char **tab_map, int *rows, int *cols)
{
	int	j;

	*rows = 0;
	*cols = 0;
	while (tab_map[*rows])
	{
		j = 0;
		while (tab_map[*rows][j])
			j++;
		if (*cols == 0)
			*cols = j;
		if (j != *cols)
			return (1);
		(*rows)++;
	}
	return (0);
}

int	check_borders(char **tab_map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if ((j == 0 || j == cols - 1 || i == 0 || i == rows - 1)
				&& tab_map[i][j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(char **argv)
{
	char	**tab_map;
	int		rows;
	int		cols;

	tab_map = get_raw_map(argv[1]);
	if (!tab_map)
		return (1);
	if (check_dimensions(tab_map, &rows, &cols) != 0)
		return (free_tab(tab_map), 1);
	if (check_borders(tab_map, rows, cols) != 0)
		return (free_tab(tab_map), 1);
	if (check_pec(tab_map, rows, cols) != 0)
		return (free_tab(tab_map), 1);
	if (shall_i_pass(tab_map, rows, cols) == 0)
		return (free_tab(tab_map), 1);
	free_tab(tab_map);
	return (0);
}
