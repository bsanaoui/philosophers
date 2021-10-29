/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:14:19 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/10/29 19:13:39 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_param	*collect_data(int argc, char *argv[])
{
	t_param	*param;

	param = malloc(sizeof (t_param));
	if (argc == 5 || argc == 6)
	{
		param->number_of_philos= ft_atoi(argv[1]);
		param->time_to_die = ft_atoi(argv[2]);
		param->time_to_eat = ft_atoi(argv[3]);
		param->time_to_sleep = ft_atoi(argv[4]);
		param->number_time_eat = -1;
		if (argc == 6)
			param->number_time_eat = ft_atoi(argv[5]);
			
	}
	else
	{
		printf("Error : Invalid Arguments\n");
		exit(EXIT_SUCCESS);
	}
	return (param);
}
