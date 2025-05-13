/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:02:16 by vmondor           #+#    #+#             */
/*   Updated: 2024/04/28 19:28:29 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_outfile(t_data *data)
{
	cleanup(data);
	free(data->pids);
	error("Outfile");
	exit(EXIT_FAILURE);
}

void	error_pid(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	perror("fork");
	exit(EXIT_FAILURE);
}

void	error(char *str)
{
	if (!str)
		str = " ";
	printf("Error\n");
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	ft_free_cmd_pipex(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (cmd == NULL || *cmd == NULL)
		return ;
	current = *cmd;
	while (current != NULL)
	{
		next = current->next;
		if (current->str)
		{
			free(current->str);
			current->str = NULL;
		}
		if (current)
			free(current);
		current = next;
	}
	*cmd = NULL;
}
