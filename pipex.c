/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:42:49 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/12 18:01:44 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	prep_env(t_data *data, int argc, char **argv)
{
	data->in = open(argv[1], O_RDONLY);
	if (data->in == -1 && !access(argv[1], F_OK))
	{
		ft_error_msg(data, argv[1], "Permission denied", 0);
		data->in_error = 1;
	}
	else if (data->in == -1 && access(argv[1], F_OK))
	{
		ft_error_msg(data, argv[1], "No such file or directory", 0);
		data->in_error = 1;
	}
	data->out = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (data->out == -1 && !access(argv[4], F_OK))
	{
		ft_error_msg(data, argv[argc - 1], "Permission denied", 0);
		data->out_error = 1;
	}
	else if (data->out == -1 && access(argv[4], F_OK))
		ft_error_msg(data, argv[argc - 1], "No such file or directory", 127);
}

static int	processor(t_data *data, pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		ft_sys_error(data, NULL);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		return (1);
	else
		return (0);
}

static void get_arguments(t_data *data, char **argv, char **envp)
{
	data->cmd1 = get_command(data, argv[2]);
	if (data->cmd1)
		data->path1 = get_command_path(data, data->cmd1, envp);
	data->curr = 2;
	data->cmd2 = get_command(data, argv[3]);
	if (data->cmd2)
		data->path2 = get_command_path(data, data->cmd2, envp);
	if (pipe(data->pipe) < 0)
		ft_sys_error(data, "PIPE");
}

int main(int argc, char **argv, char **envp)
{
	t_data		data;
	int			status;

	status = 0;
	init_data(&data);
	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		exit(1);
	}
	prep_env(&data, argc, argv);
	get_arguments(&data, argv, envp);
	fork_children(&data, envp);
	if (data.in_error == 0)
		status = processor(&data, data.pid1);
	if (data.out_error == 0)
		status = processor(&data, data.pid2);
	clear_memory(&data);
	if (status == 1)
		return (1);
	return (data.out_error);
}
