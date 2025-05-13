/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 19:08:31 by mlefort           #+#    #+#             */
/*   Updated: 2024/05/15 15:23:18 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_input(char *input)
{
	int	i;

	i = 0;
	while (ft_strcmp(input, ""))
	{
		free(input);
		return (0);
	}
	while (input[i] && input[i] == ' ')
		i++;
	if (input[i] == '\0')
	{
		free(input);
		return (0);
	}
	return (1);
}

static char	*last_char_is_pipe(char *input, t_env *try)
{
	(void)try;
	set_signal_action_heredoc(try);
	if (input[ft_strlen(input) - 1] == '|')
	{
		input = here_doc_pipe(input);
		if (!input)
		{
			if (g_erno != 130)
			{
				printf("\nsyntax error: unexpected end of file\n");
				printf("exit\n");
				return (NULL);
			}
			else
				input = ft_strdup("test");
		}
	}
	set_signal_action(try);
	return (input);
}

static void	minishell(t_cmd *cmd, t_env *try)
{
	int	nb_cmd;

	nb_cmd = 0;
	set_token(&cmd);
	nb_cmd = get_cmd_size(cmd);
	set_signal_action_fork(try);
	call_pipex(nb_cmd, cmd, try);
	set_signal_action(try);
	try->new_env = export_env_erno(try);
	ft_free_cmd(&cmd);
}

static char	*add_history_trim(char *input)
{
	char	*res;

	add_history(input);
	res = ft_strtrim(input, " ");
	free(input);
	return (res);
}

void	ft_lauch_with_env(t_env *try, t_cmd *cmd, char *input)
{
	while (input != NULL)
	{
		if (!is_valid_input(input))
		{
			input = readline("minishell > ");
			continue ;
		}
		input = add_history_trim(input);
		if (start_pipe(input) || check_quotes(input) || token_char(input))
		{
			input = readline("minishell > ");
			continue ;
		}
		input = last_char_is_pipe(input, try);
		if (!input)
			return (free(input));
		cmd = parsing(input, '|');
		if (!cmd)
		{
			input = readline("minishell > ");
			continue ;
		}
		minishell(cmd, try);
		input = readline("minishell > ");
	}
}
