/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:32:19 by mlefort           #+#    #+#             */
/*   Updated: 2024/05/05 10:53:08 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*count_for_export(char *str, char *add_to_env)
{
	int (i) = 0;
	while (str[i] && str[i] != '"' && str[i] != 39)
		i++;
	if (str[i] == '\0')
	{
		add_to_env = malloc(sizeof(char) * (i + 1));
		if (!add_to_env)
			return (NULL);
		return (add_to_env);
	}
	else
	{
		i++;
		while (str[i] && str[i] != '"' && str[i] != 39)
			i++;
	}
	add_to_env = malloc(sizeof(char) * i);
	if (!add_to_env)
		return (NULL);
	return (add_to_env);
}

char	*cpy_for_export(char *str, char *add_to_env)
{
	int (i) = 0;
	int (j) = 0;
	int (flag) = 0;
	while (str[i] && str[i] != '"' && str[i] != 39)
	{
		if (str[i] == '=')
			flag = 1;
		add_to_env[j++] = str[i++];
	}
	if (flag == 0)
		return (NULL);
	if (str[i] == '\0' && flag == 1)
	{
		add_to_env[j] = '\0';
		return (add_to_env);
	}
	else
	{
		i++;
		while (str[i] && str[i] != '"' && str[i] != 39)
			add_to_env[j++] = str[i++];
		add_to_env[j] = '\0';
	}
	return (add_to_env);
}

static char	**remplace_env(t_env *try, char *to_add, char **env, char **add)
{
	int		i;
	char	**cut;

	i = 0;
	env = malloc(sizeof(char *) * (ft_tablen(try->new_env) + 1));
	if (!env)
		return (NULL);
	while (try->new_env[i])
	{
		cut = ft_split(try->new_env[i], '=');
		if (ft_strcmp(cut[0], add[0]))
			env[i] = ft_strdup(to_add);
		else
			env[i] = ft_strdup(try->new_env[i]);
		ft_free_tab(cut);
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	**export_env(t_env *try, char *to_add)
{
	char	**env;
	char	**add;

	env = NULL;
	add = ft_split(to_add, '=');
	if (!check_in_env(try->new_env, add[0]))
	{
		env = add_env(try, to_add, env);
		ft_free_tab(add);
		ft_free_tab(try->new_env);
		return (env);
	}
	else
	{
		env = remplace_env(try, to_add, env, add);
		ft_free_tab(add);
		ft_free_tab(try->new_env);
		return (env);
	}
}

char	**add_env(t_env *try, char *to_add, char **env)
{
	int	i;

	i = 0;
	env = malloc(sizeof(char *) * (ft_tablen(try->new_env) + 2));
	if (!env)
		return (NULL);
	while (try->new_env[i])
	{
		env[i] = ft_strdup(try->new_env[i]);
		i++;
	}
	env[i] = ft_strdup(to_add);
	i++;
	env[i] = NULL;
	return (env);
}
