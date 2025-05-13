/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:53:15 by vmondor           #+#    #+#             */
/*   Updated: 2024/04/30 12:32:05 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *try)
{
	char	*pwd;

	pwd = get_env("PWD", try);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (1);
	}
	return (0);
}
