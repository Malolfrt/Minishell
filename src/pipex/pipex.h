/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmondor <vmondor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 09:30:11 by vmondor           #+#    #+#             */
/*   Updated: 2024/05/15 15:30:00 by vmondor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>	// exit
# include <stdio.h>		// perror
# include <unistd.h>	// close, access, dup, dup2, unlink, execve, fork, pipe
# include <fcntl.h>		// open
# include <errno.h>		// perror
# include <string.h>	// strerror
# include <sys/wait.h>	// for waitpid
# include <dirent.h>	// for opendir
# include <signal.h>	// for signal
# include <readline/readline.h>
# include "../../libft/libft.h"

/* TOKENS */
# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define CMD		5	//"CMD"
# define ARG		6	//"-ARG"
# define PIPE		7	//"|"

extern int	g_erno;

typedef struct s_data
{
	int		pipefd_pair[2];
	int		pipefd_impair[2];
	int		*pids;
	int		nbfork;
	int		fd_infile;
	int		fd_outfile;
	int		nb_cmd;
	char	**path;
	char	**args;
	char	*command_to_execute;
}					t_data;

typedef struct s_cmd
{
	int				index;
	int				token;
	char			*str;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char	**new_env;
	char	*new_path;
	int		erno;
}					t_env;

/* PIPEX */
int		call_pipex(int ac, t_cmd *cmd, t_env *try);
void	pipex(int ac, t_cmd *cmd, t_env *try);

/* GET_NEXT_LINE */
char	*ft_strchr(char *s, int c);
char	*ft_strcpy(char *dest, char *src);
char	*get_next_line(int fd);

/* PARSING_PIPEX */
int		parsing_pipex(char *cmd, t_data *data);
char	*parsing_start_quote(char *str);
char	*parsing_start_dot(char *str, t_env *try);

/* INIT_VALUES */
void	init_pids(t_data *data);
void	init_data(t_data *data, char *cmd, t_env *try);
void	cleanup_and_kill(t_data *data, t_cmd *cmd, t_env *try);
void	check_builtin(t_data *data, t_cmd *current, t_cmd *cmd, t_env *try);
void	cleanup(t_data *data);
void	cleanup_and_kill_builtin(t_data *data, t_cmd *cmd, t_env *try);

/* GET_PATH */
void	get_command_path(t_data *data);

/* PROCESS */
void	before_start(t_data *data, int nb_cmd);
void	wait_child(t_data *data, t_env *try);
void	parents(t_data *data, pid_t pid);
int		is_directory(char *str);
int		process_child(t_data *data, t_cmd *current, t_cmd *cmd, t_env *try);

/* PIPEX_UTILS */
void	ft_dup2(int file_dest, int file_src);
int		access_infile(t_data *data, char *infile);
int		check_access_outfile(char *outfile, int token, char **args, int i);

/* PIPEX_UTILS_NEXT */
void	free_all_pipex(t_data *data, t_cmd *cmd, t_env *try);
void	close_all(t_data *data, t_env *try);

/* CONVERT_VAR_TO_CMD */
char	*convert_var_to_cmd(char *str, t_env *try);
char	*get_env(char *str, t_env *try);

/* EXECUTE_COMMAND */
void	init_entry(t_data *data);
int		init_exit(t_cmd *current, t_data *data);
int		execute_command(t_data *data, t_cmd *current,
			t_cmd *cmd, t_env *try);

/* SET_INPUT */
char	*set_input(t_data *data, char *current);

/* SET_OUTPUT */
int		set_output(t_cmd *current, t_data *data);

/* ERROR */
void	error_outfile(t_data *data);
void	error_pid(int *pipefd);
void	error(char *str);
void	ft_free_cmd_pipex(t_cmd **cmd);

/* HERE_DOC */
char	*here_doc_pipe(char *input);
char	*is_here_doc(t_data *data, char *current);

/* HERE_DOC_UTILS */
char	*get_limiter(char **args);
char	*get_res(char **args);

void	loop_p2(char *currentline, char *line, char *limiter);
int		line_is_null(char *line);

/* SET_TOKEN */
void	set_token(t_cmd **cmd);

/* SRC/SPLIT_ARGS */
char	**split_args(char *str, char c);

/* SRC/BUILTINS */
char	*get_param(char *str);
int		ft_builtins(char **args, t_cmd *cmd, t_env *try, char *current_str);

/*	SRC/SIGNAUX	*/
void	set_signal_action_heredoc(t_env *try);
void	set_signal_action(t_env *try);
void	set_signal_action_heredoc_fork(t_env *try);
void	set_signal_action_fork(t_env *try);

/*	UTILS_FOR_ALL	*/
void	cleanup_and_kill_builtin(t_data *data, t_cmd *cmd, t_env *try);
char	*set_heredoc(t_data *data, t_cmd *current, t_cmd *cmd, t_env *try);

#endif