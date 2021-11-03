/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:24:23 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/11/03 16:52:03 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <string.h>

static void	*philosopher(void *phi)
{
	t_philo *philo;
	
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

	//*********** init mutex ************//
	forks = init_forks_mutex(p->number_of_philos);
	//*************************************//
	philos = (t_philo *)malloc(sizeof(t_philo) * p->number_of_philos);
    i = 0;
	while (i < p->number_of_philos)
	{
		philos[i].forks = forks;
		philos[i].p = p;
		philos[i].id = i + 1;
		philos[i].e_status = THINKING;
		philos[i].last_time_eat = ft_get_time();
		philos[i].nb_eat = 0;
		pthread_create(&philos[i].tid, NULL, philosopher, &philos[i]);
		i++;
	}
	return (philos);
}

static int	supervisor(t_philo *philos)
{
	int i;

	i = 0;
	while (1)
	{
		if (philos[i % philos->p->number_of_philos].e_status != EATING && (ft_get_time() - philos[i % philos->p->number_of_philos].last_time_eat) >  philos->p->time_to_die)
		{
			printf("%llu %d died\n",ft_get_time(), philos[i %  philos->p->number_of_philos].id);
			return (0);
		}
		if (are_finish_eating_nb(philos, philos->p->number_of_philos))
			return (0);
		i++;
	}
	return (1);
}

int main(int argc, char *argv[])
{
    t_param 		*param;
	t_philo			*philos;
	int		i;

    param = collect_data(argc, argv);
	// printf("%d %llu %llu %llu %d\n", param->number_of_philos, param->time_to_die, param->time_to_die, param->time_to_sleep, param->number_time_eat);
	
	//*********** Create Philos ********//
    philos = init_philos(param);
	
	//********* Supervisor **************//
	if (!supervisor(philos))
		return (0);
	//************ finally *************//
	i = -1;
	while (++i < param->number_of_philos)
		pthread_join(philos[i].tid, NULL);
	//**********************************//
	destroy_forks_mutex(philos->forks, param->number_of_philos);
    return (0);
}

// deadlock