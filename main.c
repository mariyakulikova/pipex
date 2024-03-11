/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:13:58 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/11 17:34:13 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_param	params;

	if (argc != 5)
		return (1);
	preset_params(&params, argv, envp);
	printf("%s\n infile %d\n outfile %d\n", params.path, params.infile_fd, params.outfile_fd);
	while (*(params.path_splited))
	{
		if (*(params.path_splited) == NULL)
			printf("NULL");
		printf("%s----\n", *(params.path_splited));
		params.path_splited++;
	}
	return (0);
}
