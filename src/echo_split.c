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

#include "minishell.h"

static void	loop_echo(t_echo *echo)
{
	char	quote;

	if (echo->s[echo->i] == '\'' || echo->s[echo->i] == '"')
	{
		quote = echo->s[echo->i];
		echo->strings[echo->string_index][(echo->j)++] = echo->s[(echo->i)++];
		while (echo->s[echo->i] != quote)
		{
			echo->strings[echo->string_index][echo->j] = echo->s[echo->i];
			(echo->i)++;
			(echo->j)++;
		}
		echo->strings[echo->string_index][(echo->j)++] = echo->s[(echo->i)++];
	}
	else
	{
		echo->strings[echo->string_index][echo->j] = echo->s[echo->i];
		(echo->i)++;
		(echo->j)++;
	}
}

static char	**ft_strings(char const *s, char c, t_echo *echo)
{
	echo->i = 0;
	echo->s = ft_strdup(s);
	while (echo->string_index < ft_nb_words_echo(echo->s, c))
	{
		while (echo->s[echo->i] == c)
			(echo->i)++;
		echo->strings[echo->string_index] = (char *)malloc(sizeof(char)
				* (ft_allocate_echo(&echo->s[echo->i], c) + 1));
		if (!echo->strings[echo->string_index])
			return (ft_free_strings_echo(echo->strings, echo->string_index));
		echo->j = 0;
		while (echo->s[echo->i] && echo->s[echo->i] != c)
			loop_echo(echo);
		echo->strings[echo->string_index][echo->j] = '\0';
		(echo->string_index)++;
	}
	echo->strings[echo->string_index] = NULL;
	free(echo->s);
	return (echo->strings);
}

char	**echo_split(char const *s, char c)
{
	int		nb_words;
	t_echo	echo;

	if (!s)
		return (NULL);
	nb_words = ft_nb_words_echo(s, c);
	echo.strings = malloc(sizeof(char *) * (nb_words + 1));
	if (!echo.strings)
		return (NULL);
	echo.string_index = 0;
	return (ft_strings(s, c, &echo));
}
