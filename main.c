/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:13:58 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/12 13:04:20 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// TODO delete
void	test(t_param *params)
{
	int	i = 0;
	printf("%s\n infile %d\n outfile %d\n", params->path, params->infile_fd, params->outfile_fd);
	if (*(params->path_splited) == NULL)
		printf("path_splited --------> NULL\n");
	while (*(params->path_splited + i))
	{
		printf("%s\n", *(params->path_splited + i));
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_param	params;

	if (argc != 5)
		return (1);
	preset_params(&params, argv, envp);
	test(&params); //TODO delete
	free_param(&params);
	return (0);
}
