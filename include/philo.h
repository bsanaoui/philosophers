/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsanaoui <bsanaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:24:18 by bsanaoui          #+#    #+#             */
/*   Updated: 2021/11/03 16:51:35 by bsanaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_param
{
    int			number_of_philos;
    uint64_t	time_to_die;
    uint64_t	time_to_eat;
    uint64_t	time_to_sleep;
    int			number_time_eat;

}   t_param;

typedef struct s_philo
{
	int			id;
	pthread_t   tid;
	enum
	{
		THINKING,
		EATING,
		SLEEPING,
	} e_status;
	uint64_t		last_time_eat;
	int				nb_eat;
	t_param			*p;
	pthread_mutex_t	*forks;
}	t_philo;

t_param			*collect_data(int argc, char *argv[]);
int				ft_atoi(const char *str);
pthread_mutex_t	*init_forks_mutex(int nb_fork);
int				destroy_forks_mutex(pthread_mutex_t *forks, int nb);
uint64_t		ft_get_time(void);
int				thinking(t_philo *philo);
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
int				is_pair(int	n);
int				are_finish_eating_nb(t_philo *philos, int nb);
#endif