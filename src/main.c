/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:51:12 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 14:03:11 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_erno;

static t_env	init_env(char **env, int ac, char **av)
{
	t_env	try;

	(void)ac;
	(void)av;
	try.new_env = NULL;
	try.new_env = cpy_env(env, &try);
	return (try);
}

int	ft_lauch_without_env(void)
{
	printf("Error: Required environment\n");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	*path;
	t_env	try;

	t_cmd *(cmd) = NULL;
	char *(input) = NULL;
	path = getenv("PATH");
	if (!path)
	{
		ft_lauch_without_env();
		return (g_erno);
	}
	else
	{
		try = init_env(env, ac, av);
		set_signal_action(&try);
		input = readline("minishell > ");
		ft_lauch_with_env(&try, cmd, input);
		ft_free_tab(try.new_env);
	}
	return (g_erno);
}
