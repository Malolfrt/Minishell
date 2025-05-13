/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:42:57 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/04 15:44:19 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	compare_with_absolute(t_data *data)
{
	if (access(data->args[0], F_OK) == 0)
		data->command_to_execute = ft_strdup(data->args[0]);
	else
		data->command_to_execute = NULL;
}

static int	compare_with_relative(t_data *data)
{
	int	i;

	i = 0;
	while (data->path[i])
	{
		data->path[i] = ft_strjoin(data->path[i], "/");
		data->path[i] = ft_strjoin(data->path[i], data->args[0]);
		if (access(data->path[i], F_OK) == 0)
		{
			data->command_to_execute = ft_strdup(data->path[i]);
			return (1);
		}
		i++;
	}
	data->command_to_execute = NULL;
	return (1);
}

void	get_command_path(t_data *data)
{
	if (data->args[0][0] == '/')
		compare_with_absolute(data);
	else
		compare_with_relative(data);
}
