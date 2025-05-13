/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:03:15 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/10 15:05:19 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_if_path(t_cmd *cmd, t_env *try)
{
	char	*res;
	char	*str;
	char	**args;
	t_cmd	*current;

	str = get_env("PATH", try);
	res = getenv("PATH");
	if (ft_strcmp(str, res))
	{
		free(str);
		return (1);
	}
	current = cmd;
	args = ft_split(current->str, ' ');
	if (ft_strcmp(args[0], "cd") || ft_strcmp(args[0], "export")
		|| ft_strcmp(args[0], "unset") || ft_strcmp(args[0], "exit")
		|| ft_strcmp(args[0], "expr") || ft_strcmp(args[0], "env")
		|| ft_strcmp(args[0], "pwd") || ft_strcmp(args[0], "echo"))
	{
		free(str);
		return (ft_builtins(args, cmd, try, current->str), 0);
	}
	return (ft_free_tab(args), free(str), 1);
}

int	call_pipex(int nb_cmd, t_cmd *cmd, t_env *try)
{
	char	*path;
	char	**args;

	t_cmd *(current) = cmd;
	char *(param) = NULL;
	if (!check_if_path(cmd, try))
		return (0);
	args = ft_split(current->str, ' ');
	if (!args)
		return (0);
	param = get_param(args[0]);
	if (ft_strcmp(param, "cd") || ft_strcmp(param, "export")
		|| ft_strcmp(param, "unset") || ft_strcmp(param, "exit")
		|| ft_strcmp(param, "expr"))
		return (free(param), ft_builtins(args, cmd, try, current->str));
	ft_free_tab(args);
	free(param);
	path = get_env("PATH", try);
	if (!path || !ft_strcmp(try->new_path, path))
	{
		if (path)
			free(path);
		return (printf("%s: No such file or directory\n", current->str), 0);
	}
	return (free(path), pipex(nb_cmd, cmd, try), 0);
}

void	pipex(int nb_cmd, t_cmd *cmd, t_env *try)
{
	t_data	data;
	pid_t	pid;
	t_cmd	*current;

	before_start(&data, nb_cmd);
	current = cmd;
	data.nbfork = 0;
	while (data.nbfork < (data.nb_cmd))
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			process_child(&data, current, cmd, try);
		else
			parents(&data, pid);
		data.nbfork++;
		current = current->next;
	}
	close_all(&data, try);
}
