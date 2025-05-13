/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:36:44 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 13:36:49 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_args(char **args)
{
	int	i;

	i = 0;
	if (args[1])
	{
		while (args[1][i])
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				printf("%s\n", args[1]);
				printf("exit\n");
				printf("exit: %s: numeric argument required\n", args[1]);
				return ;
			}
			i++;
		}
		g_erno = ft_atoi(args[1]);
	}
	printf("exit\n");
}

int	ft_exit(char **args, t_cmd *cmd, t_env *try, char *param)
{
	check_args(args);
	rl_clear_history();
	ft_free_tab(args);
	ft_free_tab(try->new_env);
	ft_free_cmd(&cmd);
	free(param);
	exit(g_erno);
}

void	print_result(char **new_args)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (new_args[i])
	{
		if (new_args[i][0] >= '0' && new_args[i][0] <= '9')
			res += ft_atoi(new_args[i]);
		i++;
	}
	printf("%d\n", res);
}

int	ft_expr(char **args, t_env *try)
{
	char	*temp;

	int (i) = 0;
	char **(new_args) = malloc(sizeof(char *) * (ft_tablen(args)));
	while (args[i + 1])
	{
		if (args[i + 1][0] == '$')
		{
			temp = get_env(args[i + 1] + 1, try);
			new_args[i] = ft_strdup(temp);
			free(temp);
		}
		else
			new_args[i] = ft_strdup(args[i + 1]);
		i++;
	}
	new_args[i] = NULL;
	print_result(new_args);
	ft_free_tab(new_args);
	return (1);
}
