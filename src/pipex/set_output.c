/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:36:12 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 16:10:45 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_iterator(char **args)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '"') || ft_strchr(args[i], '\''))
			quote++;
		if (quote == 2)
			return (i);
		i++;
	}
	return (0);
}

static char	*set_cmd_output(t_cmd *current, char **args)
{
	int (i) = 0;
	char *(res) = ft_strdup(args[i++]);
	while (args[i])
	{
		if (ft_strchr(args[i], '"') || ft_strchr(args[i], '\''))
		{
			res = ft_strjoin(res, " ");
			res = ft_strjoin(res, args[i++]);
			while (args[i]
				&& (!ft_strchr(args[i], '"') && !ft_strchr(args[i], '\'')))
			{
				res = ft_strjoin(res, " ");
				res = ft_strjoin(res, args[i++]);
			}
		}
		if (!ft_strcmp(args[i], ">") && !ft_strcmp(args[i], ">>"))
		{
			res = ft_strjoin(res, " ");
			res = ft_strjoin(res, args[i++]);
		}
		else
			break ;
	}
	return (free(current->str), res);
}

static void	set_fd_outfile(t_data *data, char *outfile, int token)
{
	if (token == TRUNC)
		data->fd_outfile = open(outfile, O_WRONLY | O_TRUNC);
	else
		data->fd_outfile = open(outfile, O_WRONLY | O_APPEND);
	if (data->fd_outfile == -1)
		return ;
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
	{
		close(data->fd_outfile);
		return ;
	}
	close(data->fd_outfile);
}

static char	*ft_format_outfile(char *old_outfile, char *outfile)
{
	char	*res;
	int		i;

	i = 0;
	if (outfile[i] == '>')
	{
		while (outfile[i] == '>')
			i++;
	}
	res = ft_strdup(outfile + i);
	if (old_outfile)
		free(old_outfile);
	return (res);
}

int	set_output(t_cmd *current, t_data *data)
{
	char *(outfile) = NULL;
	int (i) = 0;
	int (j) = 0;
	char **(args) = ft_split(current->str, ' ');
	i = get_iterator(args);
	while (!ft_strcmp(args[i], ">") && !ft_strcmp(args[i], ">>"))
		i++;
	while (args[++i])
	{
		j = 0;
		while (args[i][j] == '>')
			j++;
		if (args[i][j] == '\0')
			continue ;
		if (ft_strcmp(args[i - 1], ">") || ft_strcmp(args[i - 1], ">>"))
			outfile = ft_format_outfile(outfile, args[i]);
		else
			continue ;
		if (!check_access_outfile(outfile, current->token, args, i))
			return (ft_free_tab(args), free(outfile), 0);
	}
	set_fd_outfile(data, outfile, current->token);
	current->str = set_cmd_output(current, args);
	return (free(outfile), ft_free_tab(args), 1);
}
