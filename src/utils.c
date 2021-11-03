/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:14:19 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/11/03 16:51:50 by bsanaoui         ###   ########.fr       */
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

pthread_mutex_t	*init_forks_mutex(int nb_fork)
{
	pthread_mutex_t *forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * nb_fork);
	i = 0;
	while (i < nb_fork)
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

int	destroy_forks_mutex(pthread_mutex_t *forks, int nb)
{
	int	i;
	
	i = 0;
	while (i < nb)
		pthread_mutex_destroy(&forks[i++]);
	return (1);
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
	static uint64_t	first_time = 0;

	gettimeofday(&current_time, NULL);
	if (first_time == 0)
		first_time = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
	return((current_time.tv_sec * 1000 + current_time.tv_usec / 1000));
}

int	are_finish_eating_nb(t_philo *philos, int nb)
{
	int	i;

	i = -1;
	while (++i < nb)
		if (philos[i].nb_eat < philos[i].p->number_time_eat)
			return (0);
	return (1);
}