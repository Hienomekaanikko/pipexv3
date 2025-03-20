/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:37:24 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/19 14:09:26 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_path(t_data *data, char *cmd)
{
	char	*result;

	result = NULL;
	if (access(cmd, F_OK) == 0)
	{
		if (is_directory(cmd))
		{
			ft_error_msg(data, cmd, "Is a directory", 126);
			return (result);
		}
		if (access (cmd, X_OK) == 0)
		{
			result = ft_strdup(cmd);
			if (!result)
				ft_mem_error(data, "Memory allocation failed");
			return (result);
		}
		else
			ft_error_msg(data, cmd, "Permission denied", 126);
	}
	else
		ft_error_msg(data, cmd, "No such file or directory", 127);
	return (result);
}
