/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:13:02 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/05 13:55:02 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_char(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

int	ft_strchr_str(char *str, char *find)
{
	int		j;
	char	quote;

	int (i) = 0;
	if (!str || !find)
		return (0);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			while (str[++i] != quote)
				continue ;
		}
		if (str[i] == find[0])
		{
			j = 0;
			while (find[j] && str[i + j] && str[i + j] == find[j])
				j++;
			if (find[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
