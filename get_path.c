/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:02:48 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/18 13:30:46 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*test_cmd_paths(t_data *data, char *cmd)
{
	char	*final_path;
	int		i;

	i = 0;
	final_path = NULL;
	while (data->paths[i])
	{
		final_path = ft_strjoin(data->paths[i], "/");
		if (!final_path)
			ft_mem_error(data, "Memory allocation failed");
		final_path = ft_strjoin_free(final_path, cmd);
		if (!final_path)
			ft_mem_error(data, "Memory allocation failed");
		if (file_access(data, final_path))
		{
			ft_free_split(data->paths);
			data->paths = NULL;
			return (final_path);
		}
		free(final_path);
		final_path = NULL;
		i++;
	}
	cmd_not_found_msg(data);
	return (NULL);
}

static int	get_directories(t_data *data, char **envp)
{
	int	i;

	if (data->paths != NULL)
		return (1);
	i = 0;
	if (!envp[0])
	{
		unset_path_msg(data);
		return (0);
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		unset_path_msg(data);
		return (0);
	}
	data->paths = ft_split(envp[i] + 5, ':');
	if (!data->paths)
		ft_mem_error(data, "Memory allocation failed");
	return (1);
}

char	**get_command(t_data *data, char *cmd)
{
	char	**temp;

	if (!cmd || (ft_strlen(cmd) == 0) || is_space(cmd))
	{
		ft_error_msg(data, NULL, "command not found", 127);
		return (NULL);
	}
	temp = parse_cmd(cmd);
	if (!temp)
		ft_mem_error(data, "Memory allocation failed");
	return (temp);
}

char	*get_command_path(t_data *data, char **cmd, char **envp)
{
	char	*final_path;

	final_path = NULL;
	final_path = is_relative_path(data, cmd[0]);
	if (!final_path && !is_error(data))
	{
		final_path = is_absolute_path(data, cmd[0]);
		if (!final_path && !is_error(data))
		{
			if (get_directories(data, envp))
			{
				final_path = test_cmd_paths(data, cmd[0]);
				return (final_path);
			}
			return (NULL);
		}
	}
	if (is_error(data))
		return (NULL);
	return (final_path);
}
