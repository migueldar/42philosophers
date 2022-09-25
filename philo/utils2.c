/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 23:35:44 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/26 00:17:27 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long long useconds, t_philo_list *philo)
{
	struct timeval	start_time;
	struct timeval	curr_time;
	long long		start_time_u;
	long long		curr_time_u;

	gettimeofday(&start_time, NULL);
	start_time_u = start_time.tv_sec * 1000000 + start_time.tv_usec;
	gettimeofday(&curr_time, NULL);
	curr_time_u = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	while (curr_time_u - start_time_u < useconds)
	{
		usleep(500);
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		gettimeofday(&curr_time, NULL);
		curr_time_u = curr_time.tv_sec * 1000000 + curr_time.tv_usec;
	}
}

void	set_to_zero(int *fork, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*fork = 0;
	pthread_mutex_unlock(mutex);
}

char	try_to_set_one(int *fork, pthread_mutex_t *mutex)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = 0;
	if (!*fork)
	{
		*fork = 1;
		ret = 1;
	}
	pthread_mutex_unlock(mutex);
	return (ret);
}
