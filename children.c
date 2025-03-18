/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:22:32 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/18 15:04:58 by msuokas          ###   ########.fr       */
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
	if (dup2(data->in, 0) == -1)
		ft_sys_error(data, "DUP2");
	if (close(data->in) == -1)
		ft_sys_error(data, "CLOSE");
	if (dup2(data->pipe[1], 1) == -1)
		ft_sys_error(data, "DUP2");
	if (close(data->pipe[1]) == -1)
		ft_sys_error(data, "CLOSE");
	if (close(data->pipe[0]) == -1)
		ft_sys_error(data, "CLOSE");
	if (execve(path, cmd, envp) == -1)
		ft_sys_error(data, "EXECVE");
}

void	child_two(t_data *data, char *path, char **cmd, char **envp)
{
	if (dup2(data->out, 1) == -1)
		ft_sys_error(data, "DUP2");
	if (close(data->out) == -1)
		ft_sys_error(data, "CLOSE");
	if (dup2(data->pipe[0], 0) == -1)
		ft_sys_error(data, "DUP2");
	if (close(data->pipe[0]) == -1)
		ft_sys_error(data, "CLOSE");
	if (close(data->pipe[1]) == -1)
		ft_sys_error(data, "CLOSE");
	if (execve(path, cmd, envp) == -1)
		ft_sys_error(data, "EXECVE");
}
