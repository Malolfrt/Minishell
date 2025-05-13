/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:41:42 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 12:38:55 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_param(char *str)
{
	int		len;
	int		i;
	char	*param;

	len = 0;
	i = 0;
	if (!str)
		return (NULL);
	if (str[0] != '"' && str[0] != '\'')
	{
		param = ft_strdup(str);
		return (param);
	}
	i = 0;
	param = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i + 1] && (str[i + 1] != '"' && str[i + 1] != '\''))
	{
		param[i] = str[i + 1];
		i++;
	}
	param[i] = '\0';
	return (param);
}

int	ft_builtins(char **args, t_cmd *cmd, t_env *try, char *current_str)
{
	char	*param;

	param = get_param(args[0]);
	if (ft_strcmp(param, "echo"))
		ft_echo(args, try, current_str);
	else if (ft_strcmp(param, "cd"))
		ft_cd(args, try);
	else if (ft_strcmp(param, "pwd"))
		ft_pwd(try);
	else if (ft_strcmp(param, "export"))
		ft_export(args, try);
	else if (ft_strcmp(param, "unset"))
		ft_unset(args, try);
	else if (ft_strcmp(param, "env"))
		ft_env(try, 0);
	else if (ft_strcmp(param, "exit"))
		ft_exit(args, cmd, try, param);
	else if (ft_strcmp(param, "expr"))
		ft_expr(args, try);
	if (args)
		ft_free_tab(args);
	free(param);
	return (1);
}
