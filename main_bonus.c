/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulikov <mkulikov@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:30:50 by mkulikov          #+#    #+#             */
/*   Updated: 2024/03/20 16:09:50 by mkulikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_param	*param;

	if (argc < 5)
		return (0);
	param = param_init();
	set_param(param, argc, argv, envp);
	pipex(param);
	waitpids(param, param->proccesses_count);
	// free_param(param);
	return (EXIT_SUCCESS);
}
