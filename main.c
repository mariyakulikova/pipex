/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:13:58 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/18 18:01:51 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO delete
void	test(t_param *params)
{
	int	i = 0;
	printf("%s\n infile %d\n outfile %d\n", params->path, params->infile_fd, params->outfile_fd);
	if (*(params->cmds_path) == NULL)
		printf("path_splited --------> NULL\n");
	while (*(params->cmds_path + i))
	{
		printf("%s\n", *(params->cmds_path + i));
		i++;
	}
	i = 0;
	while (*(params->cmds + i))
	{
		int j = 0;
		while (*(*(params->cmds + i) + j))
		{
			printf("%s ", *(*(params->cmds + i) + j));
			printf("\n");
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_param	params;
	int		status;

	if (argc != 5)
		return (1);
	set_path_value(&params, envp);
	params.cmds_path = ft_split(params.path, ':');
	params.envp = envp;
	open_files(*(argv + 1), *(argv + 4), &params);
	parse_cmds(&params, argc, argv);
	pipex(&params);

	printf("DOZHDALSYA\n");
	free_param(&params);
	return (0);
}
