/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:14:19 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/11/06 18:15:05 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_param	*collect_data(int argc, char *argv[])
{
	t_param	*param;

	param = malloc(sizeof (t_param));
	if (argc == 5 || argc == 6)
	{
		param->nb_of_philos = ft_atoi(argv[1]);
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

int	is_pair(int	n)
{
	if (n % 2 == 0)
		return (1);
	return (0);
}

uint64_t	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000 + current_time.tv_usec / 1000));
}

void	ft_usleep(uint64_t delay)
{
	uint64_t	current;

	current = ft_get_time();
	while ((ft_get_time() - current) < delay)
		usleep(50);
}

int	ft_finalize(t_philo *philos)
{
	if (philos)
		free(philos);
	pthread_mutex_destroy(philos->display_mutex);
	destroy_forks_mutex(philos->forks, philos->p->nb_of_philos);
	return (0);
}
