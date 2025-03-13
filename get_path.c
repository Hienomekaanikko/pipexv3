/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:02:48 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/12 18:03:16 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*is_absolute_path(t_data *data, char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, F_OK) != 0)
		{
			ft_error_msg(data, cmd, "No such file or directory", 127);
			if (data->curr == 1)
				data->in_error = 1;
			if (data->curr == 2)
				data->out_error = 127;
		}
		return (cmd);
	}
	return (NULL);
}

char *get_cmd_path(t_data *data, char *cmd)
{
	char *path;
	char *final_path;
	int i;

	i = 0;
	while (data->paths[i])
	{
		path = ft_strjoin(data->paths[i], "/");
		if (!path)
			ft_sys_error(data, "Memory allocation failed");
		final_path = ft_strjoin(path, cmd);
		free(path);
		path = NULL;
		if (!final_path)
			ft_sys_error(data, "Memory allocation failed");
		if (cmd_found(data, final_path))
			return final_path;
		free(final_path);
		final_path = NULL;
		i++;
	}
	return (NULL);
}


static int	get_directories(t_data *data, char **envp)
{
	int	i;

	i = 0;
	if (!envp[0])
	{
		ft_error_msg(data, NULL, "Path not found", 127);
		return (0);
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		ft_error_msg(data, NULL, "Path not found", 127);
		return (0);
	}
	data->paths = ft_split(envp[i] + 5, ':');
	if (!data->paths)
		ft_sys_error(data, "Memory allocation failed");
	return (1);
}

char	**get_command(t_data *data, char *cmd)
{
	char **temp;

	if (!cmd || (ft_strlen(cmd) == 0) || is_space(cmd))
	{
		ft_error_msg(data, NULL, "Command not found: ", 127);
		return (NULL);
	}
	temp = parse_cmd(cmd);
	if (!temp)
		ft_sys_error(data, "Memory allocation failed");
	return (temp);
}

char	*get_command_path(t_data *data, char **cmd, char **envp)
{
	char *final_path;

	final_path = is_relative_path(cmd[0]);
	if (!final_path)
	{
		final_path = is_absolute_path(data, cmd[0]);
		if ((data->curr == 1 && data->in_error == 1)
			|| (data->curr == 2 && data->out_error == 127))
			return (NULL);
		if (!final_path)
		{
			if (get_directories(data, envp))
				final_path = get_cmd_path(data, cmd[0]);
			else
				return (NULL);
		}
	}
	if (final_path && !data->error_code)
	{
		if (!file_access(data, final_path))
			return (final_path);
	}
	else
		ft_error_msg(data, *cmd, "Command not found", 127);
	return (final_path);
}
