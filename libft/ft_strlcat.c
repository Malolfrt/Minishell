/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:24:11 by vmondor           #+#    #+#             */
/*   Updated: 2023/11/22 17:35:19 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	destlen;
	size_t	srclen;

	if (!dst && size == 0)
		return (0);
	i = 0;
	srclen = ft_strlen(src);
	destlen = ft_strlen(dst);
	j = destlen;
	if ((destlen < (size - 1)) && size > 0)
	{
		while (src[i] && (destlen + i < (size - 1)))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	if (destlen >= size)
		destlen = size;
	return (destlen + srclen);
}
