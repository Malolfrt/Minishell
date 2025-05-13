/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:41:53 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/07 17:15:28 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_command_exe(char **split_cmd)
{
	char	**args;
	char	*name_prog;
	int		i;

	args = ft_split(split_cmd[0], '/');
	name_prog = ft_strdup(args[ft_tablen(args) - 1]);
	ft_free_tab(args);
	args = malloc(sizeof(char *) * (ft_tablen(split_cmd) + 1));
	args[0] = ft_strdup(name_prog);
	free(name_prog);
	i = 1;
	while (split_cmd[i])
	{
		args[i] = ft_strdup(split_cmd[i]);
		i++;
	}
	args[i] = NULL;
	ft_free_tab(split_cmd);
	return (args);
}

static char	**get_execute_args(char *cmd)
{
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
		return (NULL);
	if (cmd[0] == '/')
		return (get_command_exe(split_cmd));
	else
		return (split_cmd);
}

void	init_entry(t_data *data)
{
	if (data->nbfork % 2 == 0 && data->nbfork != 0)
		dup2(data->pipefd_impair[0], STDIN_FILENO);
	else if (data->nbfork % 2 != 0)
		dup2(data->pipefd_pair[0], STDIN_FILENO);
	close(data->pipefd_pair[0]);
	close(data->pipefd_impair[0]);
}

int	init_exit(t_cmd *current, t_data *data)
{
	if (data->nbfork == (data->nb_cmd - 1))
	{
		if (current->token == TRUNC || current->token == APPEND)
		{
			if (!set_output(current, data))
				return (0);
			dup2(data->fd_outfile, STDOUT_FILENO);
			close(data->fd_outfile);
		}
		else
			dup2(1, STDOUT_FILENO);
	}
	else
	{
		if (data->nbfork % 2 == 0)
			dup2(data->pipefd_pair[1], STDOUT_FILENO);
		else
			dup2(data->pipefd_impair[1], STDOUT_FILENO);
	}
	close(data->pipefd_pair[1]);
	close(data->pipefd_impair[1]);
	return (1);
}

int	execute_command(t_data *data, t_cmd *current, t_cmd *cmd, t_env *try)
{
	if (parsing_pipex(current->str, data) == 0)
	{
		dup2(STDIN_FILENO, STDOUT_FILENO);
		if (data->fd_infile > -1)
			printf("%s: Command not found\n", current->str);
		cleanup_and_kill(data, cmd, try);
	}
	check_builtin(data, current, cmd, try);
	data->args = get_execute_args(current->str);
	if (execve(data->command_to_execute, data->args, try->new_env) == -1)
	{
		perror(data->command_to_execute);
		cleanup_and_kill(data, cmd, try);
	}
	return (0);
}
