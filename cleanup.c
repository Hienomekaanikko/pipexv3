/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:23:44 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/12 17:53:22 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_data *data)
{
	if (data->in != -1)
		close(data->in);
	if (data->out != -1)
		close(data->out);
	if (data->pipe[0] != -1)
		close(data->pipe[0]);
	if (data->pipe[1] != -1)
		close(data->pipe[1]);
}

void	clear_memory(t_data *data)
{
	if (data->paths)
		ft_free_split(data->paths);
	if (data->cmd1)
		ft_free_split(data->cmd1);
	if (data->cmd2)
		ft_free_split(data->cmd2);
	if (data->path1)
		free(data->path1);
	if (data->path2)
		free(data->path2);
}

void	ft_error_msg(t_data *data, char *arg, char *msg, int code)
{
	if (!data->error_code)
		data->error_code = code;
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
}

void	ft_sys_error(t_data *data, char *msg)
{
	clear_memory(data);
	if (errno && msg)
		perror(msg);
	else if (msg && !errno)
		ft_putendl_fd(msg, 2);
	exit(1);
}
