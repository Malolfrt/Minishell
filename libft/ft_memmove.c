/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:08:28 by vmondor           #+#    #+#             */
/*   Updated: 2023/11/22 18:12:55 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_temp;
	char	*src_temp;

	if (dest == src || n == 0)
		return (dest);
	if (dest < src)
	{
		dest_temp = (char *)dest;
		src_temp = (char *)src;
		while (n--)
			*dest_temp++ = *src_temp++;
	}
	else
	{
		dest_temp = (char *)dest + (n - 1);
		src_temp = (char *)src + (n - 1);
		while (n--)
			*dest_temp-- = *src_temp--;
	}
	return (dest);
}
