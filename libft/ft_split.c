/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                    		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:24:17 by vmondor           #+#    #+#             */
/*   Updated: 2023/11/26 18:16:23 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_strings(char **strings, int string_index)
{
	while (string_index--)
	{
		free(strings[string_index]);
	}
	free(strings);
	return (NULL);
}

static int	ft_nb_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static int	ft_allocate(char const *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_strings(char const *s, char c, char **strings,
								int string_index)
{
	int	i;
	int	j;

	i = 0;
	while (string_index < ft_nb_words(s, c))
	{
		while (s[i] == c)
			i++;
		strings[string_index] = (char *)malloc(sizeof(char)
				* (ft_allocate(&s[i], c) + 1));
		if (!strings[string_index])
			return (ft_free_strings(strings, string_index));
		j = 0;
		while (s[i] && s[i] != c)
		{
			strings[string_index][j] = s[i];
			i++;
			j++;
		}
		strings[string_index][j] = '\0';
		string_index++;
	}
	strings[string_index] = NULL;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	int		string_index;
	int		nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_nb_words(s, c);
	strings = malloc(sizeof(char *) * (nb_words + 1));
	if (!strings)
		return (NULL);
	string_index = 0;
	return (ft_strings(s, c, strings, string_index));
}
