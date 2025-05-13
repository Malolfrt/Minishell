/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:31:15 by mlefort           #+#    #+#             */
/*   Updated: 2024/05/15 15:26:57 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup_and_kill_builtin(t_data *data, t_cmd *cmd, t_env *try)
{
	if (data->fd_infile == -1)
	{
		if (data->args)
			ft_free_tab(data->args);
		if (data->path)
			ft_free_tab(data->path);
		if (data->pids)
			free(data->pids);
		ft_free_tab(try->new_env);
		ft_free_cmd_pipex(&cmd);
		exit(EXIT_SUCCESS);
	}
	if (data->path)
		ft_free_tab(data->path);
	if (data->args)
		ft_free_tab(data->args);
	if (data->pids)
		free(data->pids);
	if (data->command_to_execute)
		free(data->command_to_execute);
	ft_free_cmd_pipex(&cmd);
	ft_free_tab(try->new_env);
	exit (EXIT_SUCCESS);
}

char	*set_heredoc(t_data *data, t_cmd *current, t_cmd *cmd, t_env *try)
{
	set_signal_action_heredoc_fork(try);
	current->str = is_here_doc(data, current->str);
	set_token(&cmd);
	set_signal_action_fork(try);
	return (current->str);
}
