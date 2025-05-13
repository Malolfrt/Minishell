/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:16:38 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/09 20:32:59 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_token(t_cmd **cmd)
{
	t_cmd	*current;

	if (!cmd || !(*cmd))
		return ;
	current = *cmd;
	while (current)
	{
		if (ft_strchr_str(current->str, "<<"))
			current->token = HEREDOC;
		else if (ft_strchr_str(current->str, ">>"))
			current->token = APPEND;
		else if (ft_strchr_str(current->str, "<"))
			current->token = INPUT;
		else if (ft_strchr_str(current->str, ">"))
			current->token = TRUNC;
		else
			current->token = CMD;
		current = current->next;
	}
}
