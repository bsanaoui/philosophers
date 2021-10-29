/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:24:18 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/10/29 19:25:48 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>

typedef struct s_param
{
    int			number_of_philos;
    uint64_t	time_to_die;
    uint64_t	time_to_eat;
    uint64_t	time_to_sleep;
    int			number_time_eat;
	
	pthread_mutex_t mutex; //tmp
}   t_param;

typedef struct s_philo
{
	int			id;
	pthread_t   tid;
	enum
	{
		THINKING,
		DIED,
		EATING,
		SLEEPING,
	} e_status;
	t_param		*p;
}	t_philo;

t_param	*collect_data(int argc, char *argv[]);
int		ft_atoi(const char *str);

#endif