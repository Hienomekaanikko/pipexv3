/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:02:27 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/18 09:50:45 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data)
{
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->path1 = NULL;
	data->path2 = NULL;
	data->paths = NULL;
	data->in = -1;
	data->out = -1;
	data->pipe[0] = -1;
	data->pipe[1] = -1;
	data->out_error = 0;
	data->pid1 = -1;
	data->pid2 = -1;
	data->in_error = 0;
	data->curr = 1;
}
