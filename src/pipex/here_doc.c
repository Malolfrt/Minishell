/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:58:26 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 14:24:13 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*here_doc_pipe(char *input)
{
	char	*line;
	char	*get_line;
	char	*res;

	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	if (!line)
		return (free(input), NULL);
	get_line = ft_get_line(line);
	free(line);
	input = ft_strjoin(input, get_line);
	free(get_line);
	res = ft_strtrim(input, " ");
	free(input);
	if (res[ft_strlen(res) - 1] == '|')
		res = here_doc_pipe(res);
	return (res);
}

char	*is_here_doc(t_data *data, char *current)
{
	char	*line;

	char **(args) = ft_split(current, ' ');
	char *(res) = get_res(args);
	char *(limiter) = get_limiter(args);
	limiter = ft_strjoin(limiter, "\n");
	ft_putstr_fd("> ", 1);
	data->fd_infile = open(".here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	line = get_next_line(0);
	while (1)
	{
		if (line_is_null(line))
			break ;
		if (ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, data->fd_infile);
		free(line);
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
	}
	close(data->fd_infile);
	return (free(limiter), ft_free_tab(args), free(current), res);
}
