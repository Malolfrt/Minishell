/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:52:21 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 14:30:49 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_limiter(char **args)
{
	char	*limiter;
	int		i;

	i = 0;
	limiter = NULL;
	while (!ft_strcmp(args[i], "<<"))
		i++;
	i++;
	limiter = ft_strdup(args[i]);
	return (limiter);
}

char	*get_res(char **args)
{
	char	*res;

	int (i) = 0;
	if (ft_strcmp(args[0], "<<"))
		res = ft_strdup("test");
	else
		res = ft_strdup(args[i++]);
	while (!ft_strcmp(args[i], "<<"))
	{
		res = ft_strjoin(res, " ");
		res = ft_strjoin(res, args[i++]);
	}
	res = ft_strjoin(res, " ");
	res = ft_strjoin(res, ".here_doc");
	i += 2;
	while (args[i])
	{
		res = ft_strjoin(res, " ");
		res = ft_strjoin(res, args[i++]);
	}
	return (res);
}

void	loop_p2(char *currentline, char *line, char *limiter)
{
	if (access("here_doc", F_OK) == -1)
	{
		free(currentline);
		free(line);
		free(limiter);
		perror("Not exist file");
		exit(EXIT_FAILURE);
	}
	printf("%s", line);
}

int	line_is_null(char *line)
{
	if (g_erno == 130)
		return (1);
	if (!line)
	{
		free(line);
		ft_putstr_fd("\nwarning: here-document (wanted `LIMITER')\n", 0);
		return (1);
	}
	return (0);
}
