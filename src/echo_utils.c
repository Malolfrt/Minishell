/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:07:12 by mlefort           #+#    #+#             */
/*   Updated: 2024/05/15 11:48:45 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_quote(char **args, int *i, int *j)
{
	(*j)++;
	while (args[*i][*j])
	{
		if (args[*i][*j] != '\'')
			printf("%c", args[*i][*j]);
		(*j)++;
	}
}

void	double_quote(char **args, int *i, int *j, t_env *try)
{
	(*j)++;
	if (args[*i][*j] == '\'' && args[*i][*(j) + 1] == '$')
		print_var_simple_quote(args[*i] + 3, try);
	else
	{
		while (args[*i][*j])
		{
			if (args[*i][*j] != '"')
				printf("%c", args[*i][*j]);
			(*j)++;
		}
	}
}

void	without_quote(char **args, int *i, int *j, t_env *try)
{
	while (args[*i][*j])
	{
		if (args[*i][*j] == '\'')
		{
			simple_quote(args, i, j);
			return ;
		}
		else if (args[*i][*j] == '"')
		{
			double_quote(args, i, j, try);
			return ;
		}
		else
			printf("%c", args[*i][*j]);
		(*j)++;
	}
}

int	set_i(char **args)
{
	int	j;

	j = 0;
	if (args[1][0] == '"' || args[1][0] == '\'')
		j = 1;
	if (args[1][j] == '-' && args[1][j + 1] == 'n')
	{
		j++;
		while (args[1][j] && args[1][j] == 'n')
			j++;
		if (args[1][j] == '\0' || args[1][j] == '"' || args[1][j] == '\'')
			return (2);
	}
	return (1);
}

void	check_n2(char **args)
{
	if (set_i(args) == 1)
		printf("\n");
}
