/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:17:19 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/10 10:50:33 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pids(t_data *data)
{
	int	i;

	data->pids = malloc(sizeof(pid_t) * (data->nb_cmd));
	if (!data->pids)
	{
		perror("pids");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nb_cmd)
	{
		data->pids[i] = 0;
		i++;
	}
}

void	init_data(t_data *data, char *cmd, t_env *try)
{
	char	*new_path;

	new_path = get_env("PATH", try);
	data->path = ft_split(new_path, ':');
	free(new_path);
	if (!data->path)
		exit(EXIT_FAILURE);
	data->args = ft_split(cmd, ' ');
	if (!data->args)
	{
		ft_free_tab(data->path);
		exit(EXIT_FAILURE);
	}
	get_command_path(data);
}

void	cleanup_and_kill(t_data *data, t_cmd *cmd, t_env *try)
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
		exit(EXIT_FAILURE);
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
	exit (EXIT_FAILURE);
}

void	check_builtin(t_data *data, t_cmd *current, t_cmd *cmd, t_env *try)
{
	char	**args;

	args = ft_split(current->str, ' ');
	if (ft_strcmp(args[0], "env") || ft_strcmp(args[0], "pwd")
		|| ft_strcmp(args[0], "echo"))
	{
		ft_dup2(1, STDOUT_FILENO);
		ft_builtins(args, cmd, try, current->str);
		cleanup_and_kill_builtin(data, cmd, try);
	}
	else
		ft_free_tab(args);
}

void	cleanup(t_data *data)
{
	if (data->fd_infile == -1)
	{
		if (data->args)
			ft_free_tab(data->args);
		if (data->path)
			ft_free_tab(data->path);
		if (data->pids)
			free(data->pids);
		return ;
	}
	if (data->path)
		ft_free_tab(data->path);
	if (data->args)
		ft_free_tab(data->args);
	if (data->pids)
		free(data->pids);
	if (data->command_to_execute)
		free(data->command_to_execute);
}
