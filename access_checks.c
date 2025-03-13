/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:16:14 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/12 17:45:09 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *is_absolute_path(t_data *data, char *cmd)
{
	char	*result;

	result = NULL;
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, F_OK) != 0)
		{
			ft_error_msg(data, cmd, "No such file or directory", 127);
			if (data->curr == 1)
				data->in_error = 1;
			if (data->curr == 2)
				data->out_error = 127;
			return (NULL);
		}
		result = ft_strdup(cmd);
		if (!result)
			ft_sys_error(data, "Memory allocation failed");
		return (result);
	}
	return (NULL);
}

int	cmd_found(t_data *data, char *path)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (1);
		else
			ft_error_msg(data, NULL, "Permission denied", 126);
	}
	return (0);
}

char *is_relative_path(t_data *data, char *cmd)
{
	char *result;

	result = NULL;
	if (ft_strchr(cmd, '/') && cmd[0] != '/')
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		{
			result = ft_strdup(cmd);
			if (!result)
				ft_sys_error(data, "Memory allocation failed");
			return (result);
		}
	}
	return (NULL);
}


int	file_access(t_data *data, char *final_path)
{
	if (!final_path)
		return (0);
	if (access(final_path, F_OK) == 0)
	{
		if (access(final_path, X_OK) != 0)
		{
			ft_error_msg(data, final_path, "Permission denied", 126);
			return (0);
		}
		return (1);
	}
	else
		ft_error_msg(data, final_path, "Command not found", 127);
	return (0);
}
