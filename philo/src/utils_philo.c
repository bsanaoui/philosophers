/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:30:59 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/11/06 18:16:13 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	*init_forks_mutex(int nb_fork)
{
	pthread_mutex_t	*forks;
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

int	are_finish_eating_nb(t_philo *philos, int nb)
{
	int	i;

	i = -1;
	while (++i < nb)
		if (philos[i].e_status != EATING
			&& philos[i].nb_eat < philos[i].p->number_time_eat)
			return (0);
	return (1);
}
