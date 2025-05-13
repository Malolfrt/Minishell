/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:54:00 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 14:04:57 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	before_start(t_data *data, int nb_cmd)
{
	data->nb_cmd = nb_cmd;
	data->fd_infile = 0;
	init_pids(data);
	pipe(data->pipefd_impair);
	pipe(data->pipefd_pair);
}

void	wait_child(t_data *data, t_env *try)
{
	int	i;
	int	status;

	(void)try;
	i = 0;
	while (i < (data->nb_cmd))
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFEXITED(status))
			g_erno = WEXITSTATUS(status);
		i++;
	}
}

void	parents(t_data *data, pid_t pid)
{
	if (data->nbfork % 2 == 0)
	{
		close(data->pipefd_impair[0]);
		close(data->pipefd_impair[1]);
		pipe(data->pipefd_impair);
	}
	else
	{
		close(data->pipefd_pair[0]);
		close(data->pipefd_pair[1]);
		pipe(data->pipefd_pair);
	}
	data->pids[data->nbfork] = pid;
}

int	is_directory(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (dir)
	{
		printf("%s: Is a directory\n", str);
		closedir(dir);
		return (1);
	}
	closedir(dir);
	return (0);
}

int	process_child(t_data *data, t_cmd *current, t_cmd *cmd, t_env *try)
{
	if (current->str[0] == '"' || current->str[0] == '\'')
		current->str = parsing_start_quote(current->str);
	else if (current->str[0] == '$')
		current->str = convert_var_to_cmd(current->str, try);
	else if (current->str[0] == '.')
		current->str = parsing_start_dot(current->str, try);
	if (!current->str)
		free_all_pipex(data, cmd, try);
	if (is_directory(current->str))
		free_all_pipex(data, cmd, try);
	if (current->token == HEREDOC
		&& (current->str[0] != '"' && current->str[0] != '\''))
		current->str = set_heredoc(data, current, cmd, try);
	else if (current->token == INPUT)
		current->str = set_input(data, current->str);
	init_data(data, current->str, try);
	init_entry(data);
	if (init_exit(current, data) && current->str)
		execute_command(data, current, cmd, try);
	else
		cleanup_and_kill(data, cmd, try);
	return (1);
}
