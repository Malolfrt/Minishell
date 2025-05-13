/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:43:20 by mlefort           #+#    #+#             */
/*   Updated: 2024/05/05 10:41:33 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count(char *s, char c, int *count, int i)
{
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			(*count)++;
			while (s[i] && s[i] != c)
			{
				if (s[i] == '\'')
				{
					i++;
					while (s[i] && s[i] != '\'')
						i++;
				}
				if (s[i] == '"')
				{
					i++;
					while (s[i] && s[i] != '"')
						i++;
				}
				i++;
			}
		}
		while (s[i] && s[i] == c)
			i++;
	}
}

static int	ft_allocate(char *s, char c)
{
	int		i;
	int		len;
	char	quote;

	if (!s)
		return (0);
	len = (int)ft_strlen(s);
	i = 0;
	while (i < len && s[i] && s[i] != c)
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (i < len && s[i] && s[i] != quote)
				i++;
			if (i < len && s[i] == quote)
				i++;
		}
		else
			i++;
	}
	return (i);
}

void	copy_word(char *src, char *dest, char delim)
{
	char	quote;

	int (i) = 0;
	while (src[i] && src[i] != delim)
	{
		if (src[i] == '"' || src[i] == '\'')
		{
			quote = src[i];
			dest[i] = src[i];
			i++;
			while (src[i] && src[i] != quote)
			{
				dest[i] = src[i];
				i++;
			}
			dest[i] = src[i];
			i++;
		}
		else
		{
			dest[i] = src[i];
			i++;
		}
	}
	dest[i] = '\0';
}

char	*allocate_and_copy(char *s, char c)
{
	char	*str;

	int (len) = ft_allocate(s, c);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	copy_word(s, str, c);
	return (str);
}
