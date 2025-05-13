/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:36:49 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/09 18:39:18 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_char(char *input)
{
	int		i;
	char	c;

	i = 0;
	if (input[i] == '<' || input[i] == '>')
		c = input[i];
	else
		return (0);
	while (input[i])
	{
		if (input[i] != c)
			return (0);
		i++;
	}
	if (c == '<' && ft_strlen(input) <= 3)
		printf("'%s' : syntax error near unexpected token `newline'\n", input);
	else if (c == '<' && ft_strlen(input) > 3)
		printf("'%s' : syntax error near unexpected token `<<<'\n", input);
	else if (c == '>' && ft_strlen(input) <= 2)
		printf("'%s' : syntax error near unexpected token `newline'\n", input);
	else if (c == '>' && ft_strlen(input) > 2)
		printf("'%s' : syntax error near unexpected token `>'\n", input);
	free(input);
	return (2);
}

void	ft_free_cmd(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	if (cmd == NULL || *cmd == NULL)
		return ;
	current = *cmd;
	while (current != NULL)
	{
		next = current->next;
		if (current->str)
			free(current->str);
		if (current)
			free(current);
		current = next;
	}
	*cmd = NULL;
}

char	**cpy_env(char **env, t_env *try)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	new_env = malloc(sizeof(char *) * (ft_tablen(env) + 2));
	if (!new_env)
		return (NULL);
	j = 0;
	while (env[i])
	{
		if (i == 4)
		{
			new_env[j] = ft_strdup("?=0");
			j++;
		}
		new_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	new_env[j] = NULL;
	try->new_path = getenv("PATH");
	g_erno = 0;
	return (new_env);
}
