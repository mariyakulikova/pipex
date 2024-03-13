/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:13:58 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/13 11:49:01 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO delete
void	test(t_param *params)
{
	int	i = 0;
	printf("%s\n infile %d\n outfile %d\n", params->path, params->infile_fd, params->outfile_fd);
	if (*(params->cmd_path) == NULL)
		printf("path_splited --------> NULL\n");
	while (*(params->cmd_path + i))
	{
		printf("%s\n", *(params->cmd_path + i));
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_param	params;

	if (argc != 5)
		return (1);
	if (preset_params(&params, argv, envp) == 1)
		return (1);
	test(&params); //TODO delete
	pipex(&params);
	free_param(&params);
	return (0);
}
