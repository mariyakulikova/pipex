/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:13:58 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/19 18:15:09 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_param	params;
	int		status;

	if (argc != 5)
		return (1);
	preset_params(&params);
	set_path_value(&params, envp);
	params.cmds_path = ft_split(params.path, ':');
	params.envp = envp;
	open_files(*(argv + 1), *(argv + 4), &params);
	parse_cmds(&params, argc, argv);
	pipex(&params);
	close(params.infile_fd);
	close(params.outfile_fd);
	waitpid(params.pid1, NULL, 0);
	waitpid(params.pid2, NULL, 0);
	free_param(&params);
	return (0);
}
