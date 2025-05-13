/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:02:18 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 14:08:45 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup2(int file_dest, int file_src)
{
	int	dup;

	dup = dup2(file_dest, file_src);
	if (dup == -1)
	{
		perror("Error dup2");
		exit(EXIT_FAILURE);
	}
}

int	access_infile(t_data *data, char *infile)
{
	data->fd_infile = open(infile, F_OK, O_RDONLY);
	if (data->fd_infile == -1)
	{
		printf("%s: No such file or directory\n", infile);
		return (0);
	}
	else
	{
		close(data->fd_infile);
		return (1);
	}
}

static int	open_outfile(char *outfile, int token)
{
	int	fd;

	fd = 0;
	if (token == TRUNC)
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (0);
	}
	else
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (0);
	}
	close(fd);
	return (1);
}

int	check_access_outfile(char *outfile, int token, char **args, int i)
{
	if (!ft_strcmp(args[i - 1], ">") && !ft_strcmp(args[i - 1], ">>"))
		return (1);
	if (is_directory(outfile))
		return (0);
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == 0)
		return (1);
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		perror(outfile);
		return (0);
	}
	else if (access(outfile, F_OK) != 0)
	{
		if (!open_outfile(outfile, token))
			return (0);
	}
	return (1);
}
