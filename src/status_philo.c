/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:37:15 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/11/06 18:10:08 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_display(t_philo *philo, char *status, pthread_mutex_t *fork)
{
	if (fork)
		pthread_mutex_lock(fork);
	pthread_mutex_lock(philo->display_mutex);
	printf("%llu %d %s\n", ft_get_time(), philo->id, status);
	pthread_mutex_unlock(philo->display_mutex);
}

int	thinking(t_philo *philo)
{
	philo->e_status = THINKING;
	ft_display(philo, "is thinking", NULL);
	return (1);
}

static void	unlock_mutex_eating(t_philo *philo)
{
	if (is_pair(philo->id))
	{
		pthread_mutex_unlock(&philo->forks[philo->id % philo->p->nb_of_philos]);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->forks[philo->id % philo->p->nb_of_philos]);
	}
}

int	eating(t_philo *philo)
{
	if (is_pair(philo->id))
	{
		ft_display(philo, "has taken a fork",
			&philo->forks[philo->id % philo->p->nb_of_philos]);
		ft_display(philo, "has taken a fork",
			&philo->forks[philo->id - 1]);
	}
	else
	{
		ft_display(philo, "has taken a fork", &philo->forks[philo->id - 1]);
		ft_display(philo, "has taken a fork",
			&philo->forks[philo->id % philo->p->nb_of_philos]);
	}
	philo->last_time_eat = ft_get_time();
	philo->nb_eat++;
	pthread_mutex_lock(philo->display_mutex);
	printf("%llu %d is eating\n", ft_get_time(), philo->id);
	pthread_mutex_unlock(philo->display_mutex);
	ft_usleep(philo->p->time_to_eat);
	unlock_mutex_eating(philo);
	return (1);
}

int	sleeping(t_philo *philo)
{
	philo->e_status = SLEEPING;
	ft_display(philo, "is sleeping", NULL);
	ft_usleep(philo->p->time_to_sleep);
	return (1);
}
