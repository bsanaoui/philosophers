/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 12:37:15 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/11/03 16:45:23 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    ft_usleep(uint64_t delay)
{
    uint64_t current;

    current = ft_get_time();
    while ((ft_get_time() - current) < delay)
        usleep(60);
}

int	thinking(t_philo *philo)
{
    philo->e_status = THINKING;
	printf("%llu %d is thinking\n",ft_get_time(), philo->id);
    return (1);
}

int	eating(t_philo *philo)
{
    if (is_pair(philo->id))
    {
        pthread_mutex_lock(&philo->forks[philo->id % philo->p->number_of_philos]);
        printf("%llu %d has taken a fork\n",ft_get_time(), philo->id);
        pthread_mutex_lock(&philo->forks[philo->id - 1]);
        printf("%llu %d has taken a fork\n",ft_get_time(), philo->id);
    }
    else
    {
        pthread_mutex_lock(&philo->forks[philo->id - 1]);
        printf("%llu %d has taken a fork\n",ft_get_time(), philo->id);
        pthread_mutex_lock(&philo->forks[philo->id % philo->p->number_of_philos]);
        printf("%llu %d has taken a fork\n",ft_get_time(), philo->id);
    }
    philo->e_status = EATING;
    philo->nb_eat++;
    printf("%llu %d is eating\n",ft_get_time(), philo->id);
    philo->last_time_eat = ft_get_time();
    ft_usleep(philo->p->time_to_eat);
    if (is_pair(philo->id))
    {
        pthread_mutex_unlock(&philo->forks[philo->id % philo->p->number_of_philos]);
        pthread_mutex_unlock(&philo->forks[philo->id - 1]);
    }
    else
    {
        pthread_mutex_unlock(&philo->forks[philo->id - 1]);
        pthread_mutex_unlock(&philo->forks[philo->id % philo->p->number_of_philos]);
    }
	return (1);
}

int	sleeping(t_philo *philo)
{
    philo->e_status = SLEEPING;
	printf("%llu %d is sleeping\n",ft_get_time(), philo->id);
    ft_usleep(philo->p->time_to_sleep);
	return (1);
}