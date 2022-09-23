/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:51:56 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/23 02:20:00 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_dead(t_philo_list *philo)
{
	struct timeval	time_curr;
	long long		time_since_ate;

	gettimeofday(&time_curr, NULL);
	time_since_ate = (time_curr.tv_sec - philo->time_last_ate->tv_sec) * 1000;
	time_since_ate += (time_curr.tv_usec
			- philo->time_last_ate->tv_usec) / 1000;
	if (time_since_ate > (long long) philo->time_die)
	{
		printf_wrapper(4, philo);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo_list *philo)
{
	printf_wrapper(2, philo);
	ft_usleep(philo->time_sleep * 1000);
}

void	philo_think(t_philo_list *philo)
{
	printf_wrapper(3, philo);
	ft_usleep(philo->time_think * 1000);
}

void	philo_eat(t_philo_list *philo)
{
	while (1)
	{
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		if (try_to_set_one(philo->fork_right, philo->mutex_right))
		{
			if (try_to_set_one(philo->fork_left, philo->mutex_left))
			{
				gettimeofday(philo->time_last_ate, NULL);
				printf_wrapper(0, philo);
				printf_wrapper(0, philo);
				printf_wrapper(1, philo);
				ft_usleep(philo->time_eat * 1000);
				set_to_zero(philo->fork_left, philo->mutex_left);
				set_to_zero(philo->fork_right, philo->mutex_right);
				break ;
			}
			set_to_zero(philo->fork_right, philo->mutex_right);
		}
		ft_usleep(500);
	}
}

void	*philo_exec(void *philo_void)
{
	t_philo_list	*philo;

	philo = (t_philo_list *) philo_void;
	while (philo->number_eat == -1 || (philo->number_eat)-- > 0)
	{
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		philo_eat(philo);
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		philo_sleep(philo);
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
