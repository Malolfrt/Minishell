/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 20:28:37 by mlefort           #+#    #+#             */
/*   Updated: 2024/05/15 15:29:44 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler_fork(int sign)
{
	(void)sign;
	write(1, "\n", 1);
	g_erno = 130;
}

static void	sigquit_handler_fork(int sign)
{
	(void)sign;
	write(1, "Quit (core dumped)\n", 19);
	g_erno = 131;
}

void	set_signal_action_fork(t_env *try)
{
	struct sigaction	sa_quit;
	struct sigaction	sa_int;

	try->new_env = export_env_erno(try);
	sa_quit.sa_handler = &sigquit_handler_fork;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sa_int.sa_handler = &sigint_handler_fork;
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

void	set_signal_action_heredoc_fork(t_env *try)
{
	sigset_t			old_mask;
	sigset_t			mask;
	struct sigaction	sa_int;

	try->new_env = export_env_erno(try);
	sigemptyset(&mask);
	sigaddset(&mask, SIGQUIT);
	sigprocmask(SIG_BLOCK, &mask, &old_mask);
	sa_int.sa_handler = &sigint_handler_heredoc;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigprocmask(SIG_SETMASK, &old_mask, NULL);
	try->new_env = export_env_erno(try);
}
