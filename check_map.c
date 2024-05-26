/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:20:05 by aberion           #+#    #+#             */
/*   Updated: 2024/05/20 15:22:21 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/src/ft_printf.h"
#include "so_long.h"
#include "stdbool.h"
#include <stdio.h>


bool back_tracking(char **tab_map, int x, int y, int *nb_c)
{
    int move_x[] = {0, 1, 0, -1};
    int move_y[] = {1, 0, -1, 0};
    int i;
    int next_x;
    int next_y;
    i = 0;
    if (tab_map[x][y] == 'C' || tab_map[x][y] == 'E')
        (*nb_c)--;
    if (*nb_c == 0)
        return true; 
    tab_map[x][y] = 'V';
    while (i < 4)
    {
        next_x = x + move_x[i];
        next_y = y + move_y[i];
        
        if (tab_map[next_x][next_y] != 'V' && tab_map[next_x][next_y] != '1' 
        && back_tracking(tab_map, next_x, next_y, nb_c))
            return true;
        i++;
    }
    return false;        
}

int shall_i_pass(char **tab_map, int rows, int cols)
{
    int i_2;
    int j_2;
    int i;
    int j;
    int nb_c;

    nb_c = 1;
    i = 0;
    j = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if (tab_map[i][j] == 'C')
                nb_c++;
            if (tab_map[i][j] == 'P')
            {
                i_2 = i;
                j_2 = j;
            }
            j++;
        }
        i++;
    }
    if (back_tracking(tab_map, i_2, j_2, &nb_c) == false)
    {
        perror("You shall not pass");
        return 0;
    }
    return 1;
}

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
    j = 0;
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
    {
        perror("No collectible in map");
        return 1;
    }
    else if (checker_e != 1)
    {
        perror("Exit missing / too many of 'em");
        return 1;
    }
    else if (checker_p != 1)
    {
        perror("Starting position missing / too many of 'em");
        return 1;
    }
    else 
        return 0;
}

int check_map(char **argv)
{
    int i;
    int j;
    int fd;
    char **tab_map;

    i = 0;
    j = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }
    int rows = 0, cols = 0, current_col = 0;
    char *line;
    

    while ((line = get_next_line(fd)) != NULL)
    {   
        if (cols == 0)
            cols = ft_strlen(line) - 1; // Exclure '\n'
        current_col = ft_strlen(line) - 1;
        if (cols != current_col && ((line = get_next_line(fd)) != NULL))
        {
            perror("cols");
            return 1;
        }
        rows++;
        free(line);
    }
    close(fd);
    tab_map = (char **)malloc(rows * sizeof(char *));
    if (!tab_map)
        return 1;
    while (i < rows)
    {
        tab_map[i] = (char *)malloc(cols * sizeof(char));
        i++;
    }
    i = 0;
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error while opening file");
        return 1;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        j = 0;
        while (j < cols)
        {
            tab_map[i][j] = line[j];
            j++;
        }
        i++; 
        free(line);
    }
    close(fd);
    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if ((j == 0 || j == cols - 1 || i == 0 || i == rows - 1) 
            && tab_map[i][j] != '1')
            {
                perror("Frame NOK");
                return 1;
            }
            j++;
        }
        i++;
    }
    if (check_pec(tab_map, rows, cols) != 0)
        return 1;
    if (shall_i_pass(tab_map, rows, cols) == 0)
        return 1;
    // i = 0;
    // while (i < rows)
    // {
    //     j = 0;
    //     while (j < cols)
    //     {
    //         ft_printf("%c", tab_map[i][j]);
    //         j++;
    //     }
    //     ft_printf("\n");
    //     i++;
    // }
    i = 0;
    while (i < rows)
    {
        free(tab_map[i]);
        i++;
    }
    free(tab_map);
    return 0;
}
