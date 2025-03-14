#include "pipex.h"

void cmd_not_found_msg(t_data *data)
{
	if (data->curr == 1 && data->in_error != 126)
		ft_error_msg(data, data->cmd1[0], "command not found", 127);
	else if (data->curr == 2 && data->out_error != 126)
		ft_error_msg(data, data->cmd2[0], "command not found", 127);
}

void	unset_path_msg(t_data *data)
{
	if (data->curr == 1 && data->in_error == 0)
		ft_error_msg(data, data->cmd1[0], "No such file or directory", 127);
	else if (data->curr == 2 && data->out_error == 0)
		ft_error_msg(data, data->cmd2[0], "No such file or directory", 127);
}
