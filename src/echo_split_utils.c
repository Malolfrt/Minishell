/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:18:40 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/15 15:33:12 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free_strings_echo(char **strings, int string_index)
{
	while (string_index--)
	{
		free(strings[string_index]);
	}
	free(strings);
	return (NULL);
}

int	ft_nb_words_echo(char const *s, char c)
{
	char	quote;

	int (i) = 0;
	int (count) = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			if (s[i] == '\'' || s[i] == '"')
			{
				quote = s[i++];
				while (s[i] != quote)
					i++;
			}
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

int	ft_allocate_echo(char const *s, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			while (s[i] != quote)
				i++;
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}
