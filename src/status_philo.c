/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:37:15 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/10/31 13:46:30 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	thinking(t_philo *philo)
{
    philo->e_status = THINKING;
	printf("%llu %d is thinking\n",ft_get_time(), philo->id);
	return (1);
}

int	eating(t_philo *philo)
{
    pthread_mutex_lock(&philo->forks[philo->id % philo->p->number_of_philos]);
    printf("%llu %d has taken a fork\n",ft_get_time(), philo->id);
    pthread_mutex_lock(&philo->forks[philo->id - 1]);
    printf("%llu %d has taken a fork\n",ft_get_time(), philo->id);
    philo->last_time_eat = ft_get_time();
    philo->e_status = EATING;
	printf("%llu %d is eating\n",ft_get_time(), philo->id);
	usleep(philo->p->time_to_eat * 1000);
    pthread_mutex_unlock(&philo->forks[philo->id % philo->p->number_of_philos]);
    pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	return (1);
}

int	sleeping(t_philo *philo)
{
    philo->e_status = SLEEPING;
	printf("%llu %d is sleeping\n",ft_get_time(), philo->id);
	usleep(philo->p->time_to_sleep * 1000);
	return (1);
}