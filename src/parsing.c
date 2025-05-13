/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:00:03 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/06 19:11:24 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_pipe(char *input)
{
	if (!input)
		return (0);
	if (input[0] == '|')
	{
		free(input);
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	else if ((input[0] == '"' || input[0] == '\'') && input[1] == '|')
	{
		free(input);
		printf("syntax error near unexpected token `|'\n");
		return (1);
	}
	else if (input[ft_strlen(input) - 1] == '<'
		|| input[ft_strlen(input) - 1] == '>'
		|| input[0] == '>')
	{
		free(input);
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

char	**parse_args(char *input, char c)
{
	char	**args_split;
	char	**args_trim;

	int (i) = 0;
	args_split = split_args(input, c);
	if (!args_split)
	{
		free(input);
		return (NULL);
	}
	free(input);
	args_trim = malloc(sizeof(char *) * (ft_tablen(args_split) + 1));
	if (!args_trim)
	{
		ft_free_tab(args_split);
		return (NULL);
	}
	while (args_split[i])
	{
		args_trim[i] = ft_strtrim(args_split[i], " ");
		i++;
	}
	args_trim[i] = NULL;
	ft_free_tab(args_split);
	return (args_trim);
}

static t_cmd	*cmd_init(char **args)
{
	t_cmd		*cmd;
	long int	token;
	int			i;

	cmd = NULL;
	token = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\0')
		{
			ft_free_cmd(&cmd);
			return (NULL);
		}
		if (i == 0)
			cmd = ft_cmd_new(i, (int)token, args[i]);
		else
			ft_cmd_add_back(&cmd, ft_cmd_new(i, (int)token, args[i]));
		i++;
	}
	return (cmd);
}

t_cmd	*parsing(char *input, char c)
{
	char	**args;
	t_cmd	*cmd;

	cmd = NULL;
	args = parse_args(input, c);
	if (!args)
	{
		free(input);
		printf("syntax error near unexpected token `|'\n");
		return (NULL);
	}
	cmd = cmd_init(args);
	if (!cmd)
	{
		ft_free_tab(args);
		printf("syntax error near unexpected token `|'\n");
		return (NULL);
	}
	ft_free_tab(args);
	return (cmd);
}
