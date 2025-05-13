/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:49:58 by vmondor           #+#    #+#             */
/*   Updated: 2024/04/26 16:52:54 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_pwd(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
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
	return (str);
}

int	check_if_cd(t_env *try, char **args, char *oldpwd)
{
	char	*temp;
	char	*res;

	if (!args[1] || ft_strcmp(args[1], "~"))
	{
		temp = ft_strjoin_pwd("/home/", getenv("USER"));
		chdir(temp);
		res = ft_strjoin_pwd("PWD=", temp);
		free(temp);
		try->new_env = export_env(try, res);
		free(res);
		res = ft_strjoin_pwd("OLDPWD=", oldpwd);
		try->new_env = export_env(try, res);
		free(res);
		return (1);
	}
	return (0);
}

int	ft_cd(char **args, t_env *try)
{
	char	oldpwd[1024];
	char	pwd[1024];
	char	*res;

	getcwd(oldpwd, sizeof(oldpwd));
	if (check_if_cd(try, args, oldpwd))
		return (1);
	if (chdir(args[1]) == 0)
	{
		getcwd(pwd, sizeof(pwd));
		res = ft_strjoin_pwd("PWD=", pwd);
		try->new_env = export_env(try, res);
		free(res);
		res = ft_strjoin_pwd("OLDPWD=", oldpwd);
		try->new_env = export_env(try, res);
		free(res);
	}
	else
	{
		perror("chdir failed");
		return (1);
	}
	return (1);
}
