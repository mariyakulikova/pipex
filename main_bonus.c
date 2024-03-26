/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:30:50 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/26 15:34:58 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	is_argc_valid(t_param *param, int argc, char **argv)
{
	int	min_valid_amount;

	if (!ft_strcmp(argv[1], "here_doc"))
	{
		param->here_doc = 1;
		min_valid_amount = 6;
	}
	else
		min_valid_amount = 5;
	if (argc < min_valid_amount)
		return (-1);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_param	*param;
	int		i;

	param = param_init();
	if (is_argc_valid(param, argc, argv) == -1)
	{
		write(2, ERR_ARGS, ft_strlen(ERR_ARGS));
		free(param);
		return (EXIT_FAILURE);
	}
	set_param(param, argc, argv, envp);
	i = 0;
	while (i < param->cmd_num)
		child(param, i++);
	close_pipes(param);
	close_files(param);
	waitpids(param, param->cmd_num);
	free_param(param);
	return (EXIT_SUCCESS);
}
