/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:35:50 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 15:39:05 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *try, int flag)
{
	int		i;
	char	*path;

	i = 0;
	if (!try->new_env)
		return (0);
	path = get_env("PATH", try);
	if (!check_in_env(try->new_env, "PATH")
		|| !ft_strcmp(try->new_path, path))
	{
		free(path);
		printf("env: No such file or directory\n");
		return (0);
	}
	else
	{
		while (try->new_env[i])
		{
			if (flag)
				printf("export ");
			printf("%s\n", try->new_env[i++]);
		}
	}
	free(path);
	return (1);
}

static int	cpy_export(t_env *try)
{
	int		i;

	i = 0;
	if (!try->new_env)
		return (0);
	while (try->new_env[i])
		printf("export %s\n", try->new_env[i++]);
	return (1);
}

int	ft_export(char **args, t_env *try)
{
	char	*add_to_env;

	if (ft_tablen(args) == 1)
		return (cpy_export(try), 0);
	add_to_env = NULL;
	add_to_env = count_for_export(args[1], add_to_env);
	add_to_env = cpy_for_export(args[1], add_to_env);
	if (add_to_env == NULL)
	{
		free(add_to_env);
		return (1);
	}
	try->new_env = export_env(try, add_to_env);
	free(add_to_env);
	return (1);
}

int	ft_unset(char **args, t_env *try)
{
	if (check_in_env(try->new_env, args[1]))
		try->new_env = delete_in_env(try, args[1]);
	return (1);
}

char	**export_env_erno(t_env *try)
{
	char	**env;
	char	*res;
	char	*str_erno;

	if (g_erno == 1)
		g_erno = 127;
	res = ft_strdup("?=");
	str_erno = ft_itoa(g_erno);
	res = ft_strjoin(res, str_erno);
	free(str_erno);
	env = NULL;
	env = export_env(try, res);
	free(res);
	return (env);
}
