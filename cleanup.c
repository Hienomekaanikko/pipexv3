/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:23:44 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/20 14:56:03 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_data *data)
{
	if (data->in != -1)
		if (close(data->in) == -1)
			ft_sys_error(data, "CLOSE");
	if (data->out != -1)
		if (close(data->out) == -1)
			ft_sys_error(data, "CLOSE");
	if (data->pipe[0] != -1)
		if (close(data->pipe[0]) == -1)
			ft_sys_error(data, "CLOSE");
	if (data->pipe[1] != -1)
		if (close(data->pipe[1]) == -1)
			ft_sys_error(data, "CLOSE");
}

void	clear_memory(t_data *data)
{
	if (data->paths)
	{
		ft_free_split(data->paths);
		data->paths = NULL;
	}
	if (data->cmd1)
	{
		ft_free_split(data->cmd1);
		data->cmd1 = NULL;
	}
	if (data->cmd2)
	{
		ft_free_split(data->cmd2);
		data->cmd2 = NULL;
	}
	if (data->path1)
	{
		free(data->path1);
		data->path1 = NULL;
	}
	if (data->path2)
	{
		free(data->path2);
		data->path2 = NULL;
	}
}

void	ft_sys_error(t_data *data, char *msg)
{
	close_fds(data);
	clear_memory(data);
	perror(msg);
	exit(1);
}

void	ft_mem_error(t_data *data, char *msg)
{
	close_fds(data);
	clear_memory(data);
	ft_putendl_fd(msg, 2);
	exit(1);
}
