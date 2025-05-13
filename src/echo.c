/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:48:02 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/15 14:47:57 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_new_env(char *str, t_env *try)
{
	char	**cut;
	int		i;

	i = 0;
	while (try->new_env[i])
	{
		cut = ft_split(try->new_env[i], '=');
		if (ft_strcmp(cut[0], str))
		{
			ft_free_tab(cut);
			return (try->new_env[i]);
		}
		ft_free_tab(cut);
		i++;
	}
	return (NULL);
}

static int	print_var(char *str, t_env *try)
{
	char	*var;
	char	*res;

	int (i) = 0;
	int (j) = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	var = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!var)
		return (0);
	while (str[i] && str[i] != '"' )
		var[j++] = str[i++];
	var[j] = '\0';
	res = get_new_env(var, try);
	if (!res)
		printf(" ");
	else
	{
		while (*res != '=')
			res++;
		res++;
		printf("%s", res);
	}
	return (free(var), 1);
}

int	print_var_simple_quote(char *str, t_env *try)
{
	char	*var;
	char	*res;

	int (len) = 0;
	int (i) = 0;
	int (j) = 0;
	while (str[len] && str[len] != '\'')
		len++;
	var = malloc(sizeof(char) * (len + 1));
	if (!var)
		return (0);
	while (str[i] && str[i] != '\'' )
		var[j++] = str[i++];
	var[j] = '\0';
	res = get_new_env(var, try);
	if (!res)
		printf(" ");
	else
	{
		while (*res != '=')
			res++;
		res++;
		printf("'%s'", res);
	}
	return (free(var), 1);
}

int	ft_echo(char **args, t_env *try, char *current_str)
{
	int		i;
	int		j;
	char	**tab;

	if (ft_tablen(args) == 1)
		return (printf("\n"), 1);
	tab = echo_split(current_str, ' ');
	i = set_i(tab);
	while (tab[i])
	{
		j = 0;
		if ((tab[i][j] == '"' && tab[i][j + 1] == '$') || tab[i][j] == '$')
			print_var(tab[i], try);
		else if (tab[i][j] == '"' && tab[i][j + 1] != '$')
			double_quote(tab, &i, &j, try);
		else if (tab[i][j] == '\'')
			simple_quote(tab, &i, &j);
		else if (tab[i][j] != '"' && tab[i][j] != '\'')
			without_quote(tab, &i, &j, try);
		if (i < ft_tablen(tab) - 1)
			printf(" ");
		i++;
	}
	ft_free_tab(tab);
	return (check_n2(args), 1);
}
