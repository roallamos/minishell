/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migumore <migumore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:13:42 by migumore          #+#    #+#             */
/*   Updated: 2024/10/21 16:58:19 by migumore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// for printf, readline, perror
# include <stdio.h>
// for strerror
# include <string.h>
// for malloc, free, exit, getenv
# include <stdlib.h>
// for write, access, close, read, getcwd, chdir,
// unlink, execve, dup, dup2, pipe, isatty, ttyname, ttyslot
# include <unistd.h>
// stat, lstat, fstat
# include <sys/stat.h>
// for read, wait3, wait4
# include <sys/types.h>
// for read
# include <sys/uio.h>
// for open
# include <fcntl.h>
// for signal, sigaction, kill
# include <signal.h>
// for fork, kill
# include <sys/types.h>
// for waitpid, wait, waitpid, wait3, wait4
# include <sys/wait.h>
// for wait3, wait4
# include <sys/time.h>
// for wait3, wait4
# include <sys/resource.h>
// for readline, rl_on_new_line, rl_redisplay, add_history
# include <readline/readline.h> /* rl_clear_history, rl_redisplay ? */
// for readline, rl_on_new_line, rl_redisplay, add_history
# include <readline/history.h> /* rl_clear_history, rl_redisplay ? */
// for opendir, readdir, closedir
# include <dirent.h>
// for ioctl
# include <sys/ioctl.h>
// for tcsetattr, tcgetattr
# include <termios.h>
// for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>
// for tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>
// for errno
# include <errno.h>

# include "../libft/libft.h"

# define STDIN	STDIN_FILENO
# define STDOUT	STDOUT_FILENO
# define STDERR	STDERR_FILENO

# define INFILE		0
# define HEREDOC	1
# define OUTFILE	2
# define APPEND		3

# define HD_PREFIX		"/tmp/heredoc"

# define HOSTNAME_MAX_LEN	256

// Macro definition for text colors
# define BLACK			"\033[1;30m"
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define MAGENTA		"\033[0;35m"
# define CYAN			"\033[0;36m"
# define WHITE			"\033[0;37m"

// Macro definition for background colors
# define BG_RED			"\033[41m"
# define BG_GREEN		"\033[42m"
# define BG_YELLOW		"\033[43m"
# define BG_BLUE		"\033[44m"
# define BG_MAGENTA		"\033[45m"
# define BG_CYAN		"\033[46m"
# define BG_WHITE		"\033[47m"

// Macro definition for text styles
# define BOLD			"\033[1m"
# define UNDERLINE		"\033[4m"
# define RESET			"\033[0m"

// Macro definition for text styles & colors
# define BOLD_GREEN		"\033[1;32m"
# define BOLD_YELLOW	"\033[1;33m"
# define BOLD_WHITE		"\033[1;37m"

extern unsigned char	g_exit_status;

typedef struct s_docs
{
	char	*doc;
	int		flag;
	int		fd;
	int		exp;
}	t_docs;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_docs			*docs;
	int				stop_exec;
	struct s_cmd	*next;

}	t_cmd;

typedef struct s_data
{
	char		*input;
	char		*path_in_env;
	char		**path;
	char		**commands;
	int			d_quote;
	int			s_quote;
	char		**env;
	char		*pwd;
	char		*oldpwd;
	int			status;
	int			stop_exec_hd;
	pid_t		*pids;
	int			num_commands;
	int			**pipefd;
	t_cmd		*list;
	int			file_fd;
}	t_data;

void	handler(int signal);
char	*ft_find_env_var(char *envp[], char *var, int len);
char	*ft_get_cmd(char **path, char *cmd);
char	**ft_split_input(char *command, t_data *data);
char	**ft_split_args(char *s, t_data *data);
void	write_error(char *msg, char *arg);
void	write_n_change_status(char *msg, int status);
void	ft_free_lst(t_data *data);
void	ft_free_array(void **array);
void	ft_free_env(t_data *data);
void	ft_free_all(t_data *data);
void	ft_free_pids(pid_t **pids);
void	read_input(t_data *data, int is_piped);
int		check_input(char *input, t_data *data);
void	execute(t_data *data, int is_piped);
void	export(t_data *data);
int		env_size(char **arr);
void	dup_env(t_data *data, char **env);
void	get_cmd_and_execute(t_data *data, int is_piped);
void	print_env(t_data *data);
int		do_exit(t_data *data, int in_child, int is_piped);
int		ft_atoll(const char *str, long long *result);
void	do_cd(t_data *data, int pos);
void	get_pwd(t_data *data);
int		ft_istoken(int a);
t_cmd	*ft_prepare_list(t_data *data);
void	ft_lstcmdadd_back(t_cmd **lst, t_cmd *new);
void	cmds_exec(t_data *data, int is_piped);
void	wait_pids(t_data *data, int i);
int		check_builtin(t_data *data, int in_child, int is_piped);
void	full_expansor(char **args, t_data *data);
void	heredock_expansor(char **args, t_data *data);
int		delimiter_expansor(char **args, t_data *data);
char	*expand_var(t_data *data, char *args);
int		set_quotes(char c, int *d_quote, int *s_quote);
int		infile(t_data *data, int i);
int		heredoc(t_data *data, int i);
int		outfile(t_data *data, int i);
int		append(t_data *data, int i);
void	close_files(t_cmd *list);
void	open_tmp_file(t_data *data, int i);
void	delete_heredocs(t_data *data);
void	pipes_redirs(t_data *data, int i, t_cmd *list);
void	files_redirs(t_data *data, t_cmd *list);
void	close_pipes(t_data *data, int i);
void	remove_quotes(char **args, int f);
void	do_echo(t_data *data);
void	unset(t_data *data);
int		ft_lgth(const char *s1, const char *s2);
void	remove_dollar(char **args, int i, int *j, int *flag);
int		ft_isredir(char *args);
int		nb_redir(char **args);
void	redirection_type(t_docs *redir, char *args, int pos);
void	fill_redir_struct(t_docs *redir, char **args, int i, int j);
int		args_nb(const char *command, t_data *data);
void	ft_cut_cmd(char *command, char **ret);
int		only_spaces(const char *command);
int		execute_file(char *filename, t_data *data);
void	verify_input(t_data *data, int is_piped);

#endif
