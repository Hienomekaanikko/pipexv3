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

int	count_arguments(t_parse *data, const char *str)
{
	init_parse_data(data);
	while (*str)
	{
		if (ft_isspace(*str) && !data->in_quote)
			str++;
		else
		{
			data->count++;
			while (*str && (!ft_isspace(*str) || data->in_quote))
			{
				if (*str == '\'' || *str == '"')
					in_quote(str, data);
				str++;
			}
		}
	}
	return (data->count);
}

void	handle_backslash(const char **str, char *buffer, int *i, t_parse *data)
{
	if (**str == '\\' && data->quote_char != '\'')
	{
		(*str)++;
		if (**str)
			buffer[(*i)++] = **str;
	}
}

void	handle_quotes(const char **str, t_parse *data)
{
	if ((**str == '\'' || **str == '"')
		&& (!data->in_quote || **str == data->quote_char))
		in_quote(*str, data);
}
