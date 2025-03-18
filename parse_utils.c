/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msuokas <msuokas@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:40:52 by msuokas           #+#    #+#             */
/*   Updated: 2025/03/18 13:08:50 by msuokas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	skip_quoted_string(const char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && **str != quote)
		(*str)++;
	if (**str == quote)
		(*str)++;
}

int	count_arguments(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else
		{
			count++;
			while (*str && !ft_isspace(*str))
			{
				if (*str == '"' || *str == '\'')
					skip_quoted_string(&str);
				else if (*str == '\\' && *(str + 1))
					str += 2;
				else
					str++;
			}
		}
	}
	return (count);
}

void	handle_quotes(const char **str, char *buffer, int *i)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && **str != quote)
		buffer[(*i)++] = *(*str)++;
	if (**str == quote)
		(*str)++;
}

void	handle_backslash(const char **str, char *buffer, int *i)
{
	(*str)++;
	if (**str)
		buffer[(*i)++] = *(*str)++;
}
