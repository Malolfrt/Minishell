/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:14:46 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/05 10:39:35 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_nb_words(char *s, char c)
{
	int (i) = 0;
	int (count) = 0;
	if (!s)
		return (0);
	ft_count(s, c, &count, i);
	return (count);
}

static char	**ft_strings(char *s, char c, char **strings, int string_index)
{
	int	nb_words;

	int (i) = 0;
	nb_words = ft_nb_words(s, c);
	while (string_index < nb_words)
	{
		while (s[i] == c)
			i++;
		strings[string_index] = allocate_and_copy(&s[i], c);
		if (!strings[string_index])
		{
			ft_free_tab(strings);
			return (NULL);
		}
		i += ft_strlen(strings[string_index]);
		string_index++;
	}
	strings[string_index] = NULL;
	return (strings);
}

char	**split_args(char *str, char c)
{
	char	**strings;
	int		string_index;
	int		nb_words;

	nb_words = ft_nb_words(str, c);
	strings = malloc(sizeof(char *) * (nb_words + 1));
	if (!str || !strings)
		return (NULL);
	string_index = 0;
	ft_strings(str, c, strings, string_index);
	return (strings);
}
