/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:53:13 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/15 15:32:52 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "pipex/pipex.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>

extern int	g_erno;

typedef struct s_echo
{
	char	*s;
	char	**strings;
	int		string_index;
	int		i;
	int		j;
}			t_echo;

/* SIGNAUX	*/
void	set_signal_action(t_env *try);
void	set_signal_action_fork(t_env *try);
void	set_signal_action_here_doc(t_env *try);
void	set_signal_action_heredoc_fork(t_env *try);

/*	MINISHELL	*/
void	ft_lauch_with_env(t_env *try, t_cmd *cmd, char *input);

/* PARSING */
int		start_pipe(char *input);
char	**parse_args(char *input, char c);
t_cmd	*parsing(char *input, char c);

/* CHECK_QUOTES */
int		check_quotes(char *input);

/*	SPLIT_ARGS_UTILS	*/
void	ft_count(char *s, char c, int *count, int i);
void	copy_word(char *src, char *dest, char delim);
char	*allocate_and_copy(char *s, char c);

/* T_CMD_UTILS */
t_cmd	*ft_cmd_new(int i, int token, char *cmd);
void	ft_cmd_add_back(t_cmd **cmd, t_cmd *new);
int		get_cmd_size(t_cmd *cmd);

/* UTILS */
int		token_char(char *input);
void	ft_free_cmd(t_cmd **cmd);
char	**cpy_env(char **env, t_env *try);

/* BUILTINS */
int		ft_cd(char **args, t_env *try);
int		ft_exit(char **args, t_cmd *cmd, t_env *try, char *param);
int		ft_pwd(t_env *try);
int		ft_expr(char **args, t_env *try);

/*	ECHO	*/
int		print_var_simple_quote(char *str, t_env *try);
int		ft_echo(char **args, t_env *try, char *current_str);

/*	ECHO_UTILS	*/
void	simple_quote(char **args, int *i, int *j);
void	double_quote(char **args, int *i, int *j, t_env *try);
void	without_quote(char **args, int *i, int *j, t_env *try);
int		set_i(char **args);
void	check_n2(char **args);

/*	ECHO_SPLIT	*/
char	**echo_split(char const *s, char c);
char	**ft_free_strings_echo(char **strings, int string_index);
int		ft_nb_words_echo(char const *s, char c);
int		ft_allocate_echo(char const *s, char c);

/*	ENV	*/
int		ft_env(t_env *try, int flag);
int		ft_export(char **args, t_env *try);
int		ft_unset(char **args, t_env *try);
char	**export_env_erno(t_env *try);

/*	UNSET	*/
int		check_in_env(char **env, char *str);
char	**delete_in_env(t_env *try, char *str);

/*	EXPORT	*/
char	*count_for_export(char *str, char *add_to_env);
char	*cpy_for_export(char *str, char *add_to_env);
char	**export_env(t_env *try, char *to_add);
char	**add_env(t_env *try, char *to_add, char **env);

#endif