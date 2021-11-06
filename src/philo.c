/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:24:23 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/11/06 18:08:32 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>

static void	*philosopher(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (philo);
}

static t_philo	*init_philos(t_param *p)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*display_mutex;

	philos = (t_philo *)malloc(sizeof(t_philo) * p->nb_of_philos);
	forks = init_forks_mutex(p->nb_of_philos);
	display_mutex = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(display_mutex, NULL);
	i = 0;
	while (i < p->nb_of_philos)
	{
		philos[i].forks = forks;
		philos[i].p = p;
		philos[i].id = i + 1;
		philos[i].e_status = THINKING;
		philos[i].last_time_eat = ft_get_time();
		philos[i].nb_eat = 0;
		philos[i].display_mutex = display_mutex;
		pthread_create(&philos[i].tid, NULL, philosopher, &philos[i]);
		i++;
	}
	return (philos);
}

static int	supervisor(t_philo *philos)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philos[i].e_status != EATING
			&& (ft_get_time() - philos[i].last_time_eat)
			> philos->p->time_to_die)
		{
			pthread_mutex_lock(philos->display_mutex);
			printf("%llu %d died\n", ft_get_time(), philos[i].id);
			return (0);
		}
		if (philos->p->number_time_eat != -1
			&& are_finish_eating_nb(philos, philos->p->nb_of_philos))
			return (0);
		i++;
		i = i % philos->p->nb_of_philos;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_param	*param;
	t_philo	*philos;

	param = collect_data(argc, argv);
	if (!param->nb_of_philos)
	{
		if (param)
			free(param);
		return (0);
	}
	philos = init_philos(param);
	if (!supervisor(philos))
		return (ft_finalize(philos));
	return (0);
}
