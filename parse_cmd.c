/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:50:50 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/12 15:31:00 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *extract_argument(t_parse *data, const char **str)
{
	int		i;
	char	*buffer;

	i = 0;
	init_parse_data(data);
	buffer = malloc((ft_strlen(*str) + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (**str && (data->in_quote || !ft_isspace(**str)))
	{
		if (**str == '"' || **str == '\'')
			handle_quotes(str, buffer, &i);
		else if (**str == '\\')
			handle_backslash(str, buffer, &i);
		else
			buffer[i++] = *(*str)++;
	}
	buffer[i] = '\0';
	while (**str && ft_isspace(**str))
		(*str)++;
	return (buffer);
}

static int	fill_result(char **result, t_parse *data, const char **str)
{
	int	i;

	i = 0;
	while (**str)
	{
		result[i] = extract_argument(data, str);
		if (result[i] == NULL)
		{
			ft_free_split(result);
			return (0);
		}
		i++;
	}
	result[i] = NULL;
	return (1);
}

static char	**allocate_and_fill_result(t_parse *data, const char *str, int arg_count)
{
	char	**result;

	result = malloc((arg_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!fill_result(result, data, &str))
		return (NULL);
	return (result);
}

char	**parse_cmd(const char *str)
{
	t_parse	data;
	int		arg_count;

	if (!str)
		return (NULL);
	while (*str && ft_isspace(*str))
		str++;
	arg_count = count_arguments(&data, str);
	return (allocate_and_fill_result(&data, str, arg_count));
}
