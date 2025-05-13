/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:13:38 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/14 14:39:46 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(int sign)
{
	(void)sign;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_erno = 130;
}

void	set_signal_action(t_env *try)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_int;

	try->new_env = export_env_erno(try);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_int.sa_handler = &sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	sigaction(SIGINT, &sa_int, NULL);
	try->new_env = export_env_erno(try);
}

static void	sigint_handler_heredoc(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	g_erno = 130;
}

void	set_signal_action_heredoc(t_env *try)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	try->new_env = export_env_erno(try);
	sa_int.sa_handler = &sigint_handler_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	try->new_env = export_env_erno(try);
}
