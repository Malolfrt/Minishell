/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:48:31 by vmondor           #+#    #+#             */
/*   Updated: 2024/04/11 12:38:53 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;
	char	*flag;

	if ((!big || !little) && len == 0)
		return (0);
	i = 0;
	flag = (char *)big;
	little_len = ft_strlen(little);
	if (little_len == 0 || big == little)
		return (flag);
	while (flag[i] && i < len)
	{
		j = 0;
		while (flag[i + j] && little[j]
			&& flag[i + j] == little[j] && i + j < len)
			j++;
		if (j == little_len)
			return (flag + i);
		i++;
	}
	return (0);
}
