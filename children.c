/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:22:32 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/12 18:01:23 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_children(t_data *data, char **envp)
{
	if (!data->in_error)
	{
		data->pid1 = fork();
		if (data->pid1 == 0)
			child_one(data, data->path1, data->cmd1, envp);
		else if (data->pid1 == -1)
			ft_sys_error(data, "FORK");
	}
	if (!data->out_error)
	{
		data->pid2 = fork();
		if (data->pid2 == 0)
			child_two(data, data->path2, data->cmd2, envp);
		else if (data->pid2 == -1)
		{
			if (data->in != -1)
				close(data->in);
			ft_sys_error(data, "FORK");
		}
	}
	close_fds(data);
}

void	child_one(t_data *data, char *path, char **cmd, char **envp)
{
	dup2(data->in, 0);
	close(data->in);
	dup2(data->pipe[1], 1);
	close(data->pipe[1]);
	close(data->pipe[0]);
	execve(path, cmd, envp);
	close_fds(data);
	clear_memory(data);
	ft_putendl_fd("Excecve failed", 2);
	exit(1);
}

void	child_two(t_data *data, char *path, char **cmd, char **envp)
{
	dup2(data->out, 1);
	close(data->out);
	dup2(data->pipe[0], 0);
	close(data->pipe[0]);
	close(data->pipe[1]);
	execve(path, cmd, envp);
	close_fds(data);
	clear_memory(data);
	ft_putendl_fd("Excecve failed", 2);
	exit(1);
}
