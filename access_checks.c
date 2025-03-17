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

char	*is_absolute_path(t_data *data, char *cmd)
{
	char	*result;

	result = NULL;
	if (cmd[0] == '/')
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

char	*is_relative_path(t_data *data, char *cmd)
{
	char	*result;

	result = NULL;
	if ((ft_strncmp("./", cmd, 2) == 0) || (ft_strncmp("../", cmd, 3) == 0) ||
		((ft_strncmp("./", cmd, 2) != 0) && ft_strchr(cmd, '/')))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
			{
				result = ft_strdup(cmd);
				if (!result)
					ft_sys_error(data, "Memory allocation failed");
				if (is_directory(cmd))
				{
					ft_error_msg(data, cmd, "Is a directory", 126);
					return (NULL);
				}
				return (result);
			}
			ft_putstr_fd("pipex/", 2);
			ft_error_msg(data, cmd, "Permission denied", 126);
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
		if (is_directory(final_path))
			ft_error_msg(data, final_path, "command not found", 127);
		else if (access(final_path, X_OK) != 0)
		{
			ft_error_msg(data, final_path, "Permission denied", 126);
			return (0);
		}
		return (1);
	}
	return (0);
}

int	is_directory(char *cmd)
{
	int	fd;

	if (!cmd)
		return (0);
	fd = open(cmd, O_RDONLY | O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}
