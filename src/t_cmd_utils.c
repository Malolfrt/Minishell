/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:47:33 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/05 10:47:36 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*get_cmd_last(t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	return (cmd);
}

t_cmd	*ft_cmd_new(int i, int token, char *cmd)
{
	t_cmd	*new;
	int		j;

	j = 0;
	new = malloc(sizeof * new);
	if (!new)
		return (NULL);
	new->index = i;
	new->token = token;
	new->str = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!new->str)
		return (NULL);
	while (cmd[j])
	{
		new->str[j] = cmd[j];
		j++;
	}
	new->str[j] = '\0';
	new->next = NULL;
	return (new);
}

void	ft_cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (!new)
		return ;
	if (!*cmd)
	{
		*cmd = new;
		return ;
	}
	last = get_cmd_last(*cmd);
	last->next = new;
}

int	get_cmd_size(t_cmd *cmd)
{
	int	size;

	size = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		cmd = cmd->next;
		size++;
	}
	return (size);
}
