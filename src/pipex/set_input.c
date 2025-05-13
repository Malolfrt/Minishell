/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:36:12 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 14:17:11 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_nb_char(char **tab)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tab[i])
	{
		count += ft_strlen(tab[i]);
		i++;
		count++;
	}
	return (count);
}

static char	*ft_tab_to_str(char **tab)
{
	char	*str;
	int		j;

	int (i) = 0;
	int (it) = 0;
	if (!tab)
		return (NULL);
	str = NULL;
	str = malloc(sizeof(char) * (ft_nb_char(tab) + 1));
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			str[it++] = tab[i][j++];
		i++;
		if (tab[i])
			str[it++] = ' ';
	}
	str[it] = '\0';
	ft_free_tab(tab);
	return (str);
}

static int	check_is_valid_input(t_data *data, char **args, char *find)
{
	if (!access_infile(data, args[1]))
	{
		ft_free_tab(args);
		return (0);
	}
	if (!ft_strcmp(args[0], find))
	{
		ft_free_tab(args);
		return (0);
	}
	return (1);
}

char	*set_input(t_data *data, char *current)
{
	char	**args;
	char	**res;
	char	*str;

	int (it) = 0;
	int (i) = 2;
	str = NULL;
	args = ft_split(current, ' ');
	if (!check_is_valid_input(data, args, "<"))
		return (current);
	res = malloc(sizeof(char *) * (ft_tablen(args) + 1));
	if (!res)
	{
		ft_free_tab(args);
		return (NULL);
	}
	while (args[i])
		res[it++] = ft_strdup(args[i++]);
	res[it++] = ft_strdup(args[1]);
	res[it] = NULL;
	ft_free_tab(args);
	str = ft_tab_to_str(res);
	free(current);
	return (str);
}
