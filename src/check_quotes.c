/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:06:20 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/06 18:02:19 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quote(char *input, char c, int i)
{
	int	quote;

	quote = 1;
	i++;
	while (input[i])
	{
		if (input[i] == c)
			quote++;
		i++;
	}
	if (quote % 2 != 0)
	{
		free(input);
		printf("syntax error near unexpected token `%c'\n", c);
		return (1);
	}
	return (0);
}

int	check_quotes(char *input)
{
	int	count;

	int (i) = 0;
	if (!input)
		return (0);
	count = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			count = count_quote(input, '\'', i);
			break ;
		}
		else if (input[i] == '"')
		{
			count = count_quote(input, '"', i);
			break ;
		}
		else
			i++;
	}
	return (count);
}
