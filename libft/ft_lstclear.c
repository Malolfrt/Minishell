/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:22:45 by vmondor           #+#    #+#             */
/*   Updated: 2023/11/20 19:09:47 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*now;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		now = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = now;
	}
	*lst = NULL;
}
