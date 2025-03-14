/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:28:37 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/12 17:44:26 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_data
{
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd1;
	char	**cmd2;
	char	**paths;
	char	*path1;
	char	*path2;
	int		pipe[2];
	int		in;
	int		out;
	int		out_error;
	int		in_error;
	int		curr;
}	t_data;

typedef struct s_parse
{
	int			count;
	int			in_quote;
	char		quote_char;
	char		*buffer;
}	t_parse;

void	init_parse_data(t_parse *data);
void	init_data(t_data *data);

char	**get_command(t_data *data, char *cmd);
char	**parse_cmd(const char *str);
char	*get_command_path(t_data *data, char **cmd, char **envp);
char	*is_relative_path(t_data *data, char *cmd);
char	*is_absolute_path(t_data *data, char *cmd);
char	*test_cmd_paths(t_data *data, char *cmd);
int		file_access(t_data *data, char *final_path);
int		is_directory(char *cmd);

void	child_one(t_data *data, char *path, char **cmd, char **envp);
void	child_two(t_data *data, char *path, char **cmd, char **envp);
void	fork_children(t_data *data, char **envp);

int		count_arguments(const char *str);
void	handle_backslash(const char **str, char *buffer, int *i);
void	handle_quotes(const char **str, char *buffer, int *i);

void	close_fds(t_data *data);
void	ft_error_msg(t_data *data, char *arg, char *msg, int code);
void	clear_memory(t_data *data);
void	ft_sys_error(t_data *data, char *msg);
void	unset_path_msg(t_data *data);
void	cmd_not_found_msg(t_data *data);

#endif
