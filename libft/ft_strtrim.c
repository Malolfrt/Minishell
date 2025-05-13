/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:52:24 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/02 19:16:37 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_begin(char const *s1, char const *set)
{
	size_t	i;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	i = 0;
	while (i < len_s1)
	{
		if (ft_strchr_char(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static size_t	ft_end(char const *s1, char const *set)
{
	size_t	i;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	i = 0;
	while (i < len_s1)
	{
		if (ft_strchr_char(set, s1[len_s1 - i - 1]) == 0)
			break ;
		i++;
	}
	return (len_s1 - i);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	size_t	begin;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	begin = ft_begin(s1, set);
	end = ft_end(s1, set);
	if (begin >= end)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end - begin + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + begin, end - begin + 1);
	return (str);
}
