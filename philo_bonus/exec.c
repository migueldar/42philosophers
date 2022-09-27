/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:51:56 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 23:19:28 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_philo_dead(void *philo_void)
{
	struct timeval	time_curr;
	long long		time_since_ate;
	t_philo			*philo;

	philo = (t_philo *)philo_void;
	while (1)
	{
		gettimeofday(&time_curr, NULL);
		sem_wait(philo->mutex_time);
		time_since_ate = (time_curr.tv_sec - philo->time_last_ate.tv_sec)
			* 1000;
		time_since_ate += (time_curr.tv_usec
				- philo->time_last_ate.tv_usec) / 1000;
		sem_post(philo->mutex_time);
		if (time_since_ate > (long long) philo->time_die)
		{
			printf_wrapper(4, philo);
			exit(0);
		}
		ft_usleep(500);
	}
	return (NULL);
}

void	philo_exec(int num, t_philo *philo)
{
	pthread_t	check_death;

	philo->id = num;
	pthread_create(&check_death, NULL, check_philo_dead, philo);
	pthread_detach(check_death);
	philo_loop(philo);
	exit(0);
}
