/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodralva <rodralva@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:13:42 by migumore          #+#    #+#             */
/*   Updated: 2024/06/26 18:22:44 by rodralva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(MINISHELL_H)
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

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

# define HOSTNAME_MAX_LEN 256

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

typedef struct s_data
{
	char		*input;
	char		*path_in_env;
	char		**path;
	char		**tokens;
	char		**commands;
	int			cmd_pos;
	char		**args;
	char		*cmd;
	char		**env;
	char		*pwd;
	char		*prompt;
	int			status;
	int			cap;
	int			size;
	const char	*pos;
	const char	*start;
	char		quote;
	pid_t		pids;
	int			num_commands;
	char		*limiter;
	char		*infile;
	char		*outfile;
	int			fd_infile;
	int			fd_outfile;
	int			pipefd[2];
}	t_data;

typedef struct	s_list
{
	char	*command;
	char	**args;
	char	**outfile;
	char	**infile;
	char	**heredock;
	char	**migu_dale_nombre;
	t_list	*next;
}	t_commad_list;

void	handler(int signal);
char	*ft_find_path(char *envp[]);
char	*ft_get_cmd(char **path, char *cmd);
char	**ft_split_input(const char *command, t_data *data);
void	write_error(char *msg, char *arg);
void	ft_free_args(t_data *data);
void	ft_free_path(t_data *data);
void	ft_free_env(t_data *data);
void	ft_free_cmds_n_limiter_n_pids(t_data *data);
void	read_input(t_data *data);
int		check_input(char *input);
void	parse(t_data *data);
void	export(t_data *data, int pos);
int		env_size(char **arr);
void	dup_env(t_data *data, char **env);
void	get_cmd_and_execute(t_data *data);
void	print_env(t_data *data);
void	ft_pwd(t_data *data);
void	set_prompt(t_data *data);
void	do_exit(t_data *data);
void	do_cd(t_data *data, int pos);
int	ft_istoken(int a);

#endif // MINISHELL_H
