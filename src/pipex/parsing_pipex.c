/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:13:29 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/09 12:38:53 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	command_exist(char *cmd)
{
	char	**path;
	char	*new_path;

	int (i) = 0;
	new_path = getenv("PATH");
	path = ft_split(new_path, ':');
	if (!path)
		return (0);
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd);
		i++;
	}
	i = 0;
	while (path[i])
	{
		if (access(path[i], F_OK) == 0)
		{
			ft_free_tab(path);
			return (1);
		}
		i++;
	}
	return (ft_free_tab(path), 0);
}

int	parsing_pipex(char *cmd, t_data *data)
{
	char	**args;

	if (data->fd_infile == -1)
		return (0);
	args = ft_split(cmd, ' ');
	if (!args)
		return (0);
	if (cmd[0] == '/')
	{
		if (access(args[0], F_OK) == -1)
			return (ft_free_tab(args), 0);
	}
	else
	{
		if (command_exist(args[0]) == 0)
			return (ft_free_tab(args), 0);
	}
	ft_free_tab(args);
	return (1);
}

static char	*return_res_and_free(char **res, char **str)
{
	*res = ft_strdup(*str);
	if (!*res)
	{
		free(*str);
		return (NULL);
	}
	free(*str);
	return (*res);
}

char	*parsing_start_quote(char *str)
{
	char (quote) = str[0];
	char *(res) = NULL;
	int (i) = 1;
	int (j) = 0;
	while (str[i] && str[i] != quote)
	{
		if (!(str[i] >= 97 && str[i] <= 122) && str[i] != '/')
			return (return_res_and_free(&res, &str));
		i++;
	}
	if (str[i] == quote)
	{
		i = 1;
		res = malloc(sizeof(char) * (ft_strlen(str) - 1));
		if (!res)
			return (NULL);
	}
	while (str[i] && str[i] != quote)
		res[j++] = str[i++];
	if (!str[i + 1])
		return (free(str), res[j] = '\0', res);
	while (str[++i])
		res[j++] = str[i];
	return (res[j] = '\0', free(str), res);
}

char	*parsing_start_dot(char *str, t_env *try)
{
	char	*prog_name;
	char	*res;

	if (!str)
		return (NULL);
	if (str[1] != '/')
		return (str);
	prog_name = ft_strdup(str + 2);
	if (access(prog_name, F_OK) == -1)
		return (free(prog_name), free(str), NULL);
	res = get_env("PWD", try);
	if (!res)
		return (free(prog_name), free(str), NULL);
	res = ft_strjoin(res, "/");
	if (!res)
		return (free(prog_name), free(str), NULL);
	res = ft_strjoin(res, prog_name);
	free(str);
	free(prog_name);
	return (res);
}
