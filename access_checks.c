/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:16:14 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/19 13:47:46 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*is_absolute_path(t_data *data, char *cmd)
{
	char	*result;

	result = NULL;
	if (cmd[0] == '/')
		result = check_path(data, cmd);
	return (result);
}

char	*is_relative_path(t_data *data, char *cmd)
{
	char	*result;

	result = NULL;
	if ((ft_strncmp("./", cmd, 2) == 0) || (ft_strncmp("../", cmd, 3) == 0)
		|| (cmd[0] != '/' && ft_strchr(cmd, '/')))
		result = check_path(data, cmd);
	return (result);
}

int	file_access(t_data *data, char *path)
{
	if (!path)
		return (0);
	if (access(path, F_OK) == 0)
	{
		if (is_directory(path))
			ft_error_msg(data, path, "Is a directory", 127);
		if (access(path, X_OK) != 0)
		{
			ft_error_msg(data, path, "Permission denied", 126);
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
	fd = open(cmd, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (1);
	}
	return (0);
}
