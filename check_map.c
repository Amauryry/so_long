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


int check_pec(char **tab_map, int rows, int cols)
{
    int i;
    int j;
    int checker_e;
    int checker_c;
    int checker_p;
    
    checker_e = 0;
    checker_c = 0;
    checker_p = 0;
    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if (tab_map[i][j] == 'P')
                checker_p++;
            if (tab_map[i][j] == 'E')
                checker_e++;
            if (tab_map[i][j] == 'C')
                checker_c++;
            j++;
        }
        i++;
    }
    if (checker_c < 1)
        return 1;
    else if (checker_e != 1)
        return 1;
    else if (checker_p != 1)
        return 1;
    return 0;
}

int check_map(char **argv)
{
    int i;
    int j;
    char **tab_map;
    int rows;
    int cols;
    
    rows = 0;
    cols = 0;
    
    tab_map = get_raw_map(argv[1]);
    while (tab_map[rows])
    {
        j = 0;
        while(tab_map[rows][j])
            j++;
        if (cols == 0)
            cols = j;
        if (j != cols)
            return (free_tab(tab_map), 1);
        rows++;
    }
    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if ((j == 0 || j == cols - 1 || i == 0 || i == rows - 1) 
            && tab_map[i][j] != '1')
                return (free_tab(tab_map), 1);
            j++;
        }
        i++;
    }
    if (check_pec(tab_map, rows, cols) != 0)
        return (free_tab(tab_map), 1);
    if (shall_i_pass(tab_map, rows, cols) == 0)
        return (free_tab(tab_map), 1);
    free_tab(tab_map);
    return 0;
}
