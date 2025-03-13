/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:02:27 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/12 17:44:56 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_parse_data(t_parse *data)
{
	data->count = 0;
	data->in_quote = 0;
	data->quote_char = '\0';
}

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
	data->in_error = 0;
	data->curr = 1;
}
