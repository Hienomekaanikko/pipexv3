#include "pipex.h"

void	in_quote(const char *str, t_parse *data)
{
	if (!data->in_quote)
	{
		data->in_quote = 1;
		data->quote_char = *str;
	}
	else if (*str == data->quote_char)
	{
		data->in_quote = 0;
		data->quote_char = '\0';
	}
}

int count_arguments(t_parse *data, const char *str)
{
	char	quote;

	init_parse_data(data);
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else
		{
			data->count++;
			while (*str && !ft_isspace(*str))
			{
				if (*str == '"' || *str == '\'')
				{
					quote = *str++;
					while (*str && *str != quote)
						str++;
					if (*str == quote)
						str++;
				}
				else if (*str == '\\' && *(str + 1))
					str += 2;
				else
					str++;
			}
		}
	}
	return (data->count);
}

void handle_quotes(const char **str, char *buffer, int *i)
{
	char quote;

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
