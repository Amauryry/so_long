/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberion <aberion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:02:56 by aberion           #+#    #+#             */
/*   Updated: 2024/06/03 14:00:55 by aberion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	chains;

	chains = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		if (s[i] == c)
			return (-1);
		if (s[i])
			chains++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (chains);
}

char	*mettre_mot(const char *s, size_t start, size_t end)
{
	char	*word;
	size_t	i;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = 0;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	ssize_t	i;
	ssize_t	j;
	size_t	start;
	ssize_t	chains;
	char	**tabchains;

	chains = count_words(s, c);
	if (chains == -1)
		return (NULL);
	tabchains = malloc((chains + 1) * sizeof(char *));
	if (!tabchains)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (s[i] && j < chains)
	{
		while (s[i++] == c)
			start = i;
		while (s[i] && s[i] != c)
			i++;
		tabchains[j++] = mettre_mot(s, start, i);
	}
	tabchains[j] = 0;
	return (tabchains);
}
