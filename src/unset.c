/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:08:08 by mlefort           #+#    #+#             */
/*   Updated: 2024/04/30 13:19:35 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in_env(char **env, char *str)
{
	int		i;
	char	**cut;

	i = 0;
	while (env[i])
	{
		cut = ft_split(env[i], '=');
		if (ft_strcmp(cut[0], str))
		{
			ft_free_tab(cut);
			return (1);
		}
		ft_free_tab(cut);
		i++;
	}
	return (0);
}

char	**delete_in_env(t_env *try, char *str)
{
	int		i;
	int		j;
	char	**cut;
	char	**env;

	i = 0;
	j = 0;
	env = malloc(sizeof(char *) * ft_tablen(try->new_env));
	if (!env)
		return (NULL);
	while (try->new_env[i])
	{
		cut = ft_split(try->new_env[i], '=');
		if (!ft_strcmp(cut[0], str))
		{
			env[j] = ft_strdup(try->new_env[i]);
			j++;
		}
		ft_free_tab(cut);
		i++;
	}
	env[j] = NULL;
	ft_free_tab(try->new_env);
	return (env);
}
