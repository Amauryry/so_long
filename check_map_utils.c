/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:50:20 by aberion           #+#    #+#             */
/*   Updated: 2024/05/27 13:53:42 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
        return 0;
    return 1;
}
char    *ft_realloc(char *ptr, size_t size)
{
    char    *self;

    free(ptr);
    self = ft_calloc((size + 1), sizeof(char));
    if (!self)
        exit(EXIT_FAILURE);
    return (self);
}

char **get_raw_map(char *map_path)
{
    int        fd_map;
    int        bytes_read;
    int        read_size;
    char    *raw_map;

    bytes_read = 1;
    read_size = 1024;
    raw_map = ft_calloc(read_size, sizeof(char));
    if (!raw_map)
        exit(EXIT_FAILURE);
    while (1)
    {
        fd_map = open(map_path, O_RDONLY);
        if (!fd_map)
            exit(EXIT_FAILURE);
        bytes_read = read(fd_map, raw_map, read_size);
        if (bytes_read < read_size)
            break ;
        read_size <<= 1;
        raw_map = ft_realloc(raw_map, read_size);
        close(fd_map);
    }
    close(fd_map);
    char **new = ft_split(raw_map, '\n');
    return (free(raw_map), new);
}
