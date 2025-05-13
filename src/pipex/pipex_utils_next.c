/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:06:54 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 14:38:59 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all_pipex(t_data *data, t_cmd *cmd, t_env *try)
{
	free(data->pids);
	ft_free_cmd_pipex(&cmd);
	ft_free_tab(try->new_env);
	exit(EXIT_FAILURE);
}

void	close_all(t_data *data, t_env *try)
{
	close(data->pipefd_pair[0]);
	close(data->pipefd_impair[0]);
	close(data->pipefd_pair[1]);
	close(data->pipefd_impair[1]);
	wait_child(data, try);
	free(data->pids);
}
