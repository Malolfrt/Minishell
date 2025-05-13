/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_var_to_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:44:22 by vmondor           #+#    #+#             */
/*   Updated: 2024/04/30 17:38:30 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_join(char *s1, char *s2)
{
	char	*str;

	int (i) = -1;
	int (j) = 0;
	if (!s1 || !s2)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	if (s1)
		while (s1[++i])
			str[i] = s1[i];
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*get_env(char *str, t_env *try)
{
	char	**cut;
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (try->new_env[i])
	{
		cut = ft_split(try->new_env[i], '=');
		if (ft_strcmp(cut[0], str))
		{
			res = ft_strdup(cut[ft_tablen(cut) - 1]);
			ft_free_tab(cut);
			return (res);
		}
		ft_free_tab(cut);
		i++;
	}
	return (NULL);
}

static void	ft_free_all(char **args, char *res, char *str)
{
	ft_free_tab(args);
	free(res);
	free(str);
}

char	*convert_var_to_cmd(char *str, t_env *try)
{
	char	*res;
	char	**args;

	int (i) = 0;
	args = ft_split(str, ' ');
	res = get_env(args[i] + 1, try);
	if (!res)
	{
		ft_free_tab(args);
		free(str);
		return (NULL);
	}
	i++;
	while (args[i])
	{
		res = ft_join(res, " ");
		if (args[i][0] == '$')
			res = ft_join(res, get_env(args[i] + 1, try));
		else
			res = ft_join(res, args[i]);
		if (!res)
			return (ft_free_all(args, res, str), NULL);
		i++;
	}
	return (ft_free_tab(args), free(str), res);
}
