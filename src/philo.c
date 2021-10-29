/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:24:23 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/10/29 19:31:38 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>

void	*philosopher(void *phi)
{
	t_philo *philo;

	philo = (t_philo *)phi;
	pthread_mutex_lock(&philo->p->mutex);
	write(1, "Number PHILOS = ", 16);
	printf("%d", philo->id);
	write (1, "\n", 1);
	pthread_mutex_unlock(&philo->p->mutex);
	return (philo);
}

t_philo	*create_philos(t_param *p)
{
	int		i;
	t_philo	*philos;

	philos = (t_philo *)malloc(sizeof(t_philo) * p->number_of_philos);
    i = 0;
	while (i < p->number_of_philos)
	{
		philos[i].p = p;
		philos[i].id = i;
		philos[i].e_status = THINKING;
		pthread_create(&philos[i].tid, NULL, philosopher, &philos[i]);
		i++;
	}
	return (philos);
}

int main(int argc, char *argv[])
{
    t_param *param;
	t_philo	*philos;
	int		i;

    param = collect_data(argc, argv);
	printf("%d %llu %llu %llu %d\n", param->number_of_philos, param->time_to_die, param->time_to_die, param->time_to_sleep, param->number_time_eat);

	//*********** init mutex ***********//
	pthread_mutex_init(&param->mutex, NULL);
	//*********** Create Philos *******//
    philos = create_philos(param);
	//**********************************//
	i = -1;
	while (++i < param->number_of_philos)
		pthread_join(philos[i].tid, NULL);
	//*********************************//
	pthread_mutex_destroy(&param->mutex);
    return (0);
}