/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:53:34 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/18 12:59:57 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_not_found_msg(t_data *data)
{
	if (data->curr == 1 && data->in_error == 0)
		ft_error_msg(data, data->cmd1[0], "command not found", 1);
	else if (data->curr == 2 && data->out_error == 0)
		ft_error_msg(data, data->cmd2[0], "command not found", 127);
}

void	unset_path_msg(t_data *data)
{
	if (data->curr == 1 && data->in_error == 0)
		ft_error_msg(data, data->cmd1[0], "command not found", 1);
	else if (data->curr == 2 && data->out_error == 0)
		ft_error_msg(data, data->cmd2[0], "command not found", 127);
}

int	is_error(t_data *data)
{
	if ((data->curr == 1 && data->in_error)
		|| (data->curr == 2 && data->out_error))
		return (1);
	return (0);
}

void	ft_error_msg(t_data *data, char *arg, char *msg, int code)
{
	if (data->curr == 1 && !data->in_error)
		data->in_error = code;
	if (data->curr == 2 && !data->out_error)
		data->out_error = code;
	ft_putstr_fd(msg, 2);
	if (arg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
	}
	ft_putstr_fd("\n", 2);
}
