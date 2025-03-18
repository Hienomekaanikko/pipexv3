/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:42:49 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/18 13:29:27 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	prep_files(t_data *data, int argc, char **argv)
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
	{
		ft_error_msg(data, argv[argc - 1], "No such file or directory", 127);
		data->out_error = 1;
	}
}

static int	processor(t_data *data, pid_t pid2)
{
	int		processes;
	int		status;
	int		exit_code;
	pid_t	pid;

	processes = 2;
	status = -1;
	exit_code = 0;
	pid = -1;
	while (processes > 0)
	{
		pid = wait(&status);
		if (pid == pid2 && WIFEXITED(status)
			&& WEXITSTATUS(status) == 1)
			exit_code = 1;
		processes--;
	}
	if (exit_code)
		return (1);
	return (data->out_error);
}

static void	get_arguments(t_data *data, char **argv, char **envp)
{
	if (data->in_error == 0)
	{
		data->cmd1 = get_command(data, argv[2]);
		if (data->cmd1)
			data->path1 = get_command_path(data, data->cmd1, envp);
	}
	if (data->out_error == 0)
	{
		data->curr = 2;
		data->cmd2 = get_command(data, argv[3]);
		if (data->cmd2)
			data->path2 = get_command_path(data, data->cmd2, envp);
	}
	if (pipe(data->pipe) < 0)
		ft_sys_error(data, "PIPE");
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	init_data(&data);
	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2);
		return (0);
	}
	prep_files(&data, argc, argv);
	get_arguments(&data, argv, envp);
	fork_children(&data, envp);
	clear_memory(&data);
	return (processor(&data, data.pid2));
}
