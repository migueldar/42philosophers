/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:51:56 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/22 02:44:10 by mde-arpe         ###   ########.fr       */
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
		printf_wrapper(4, philo->mutex_write, philo->id, philo->time_init);
		end_to_true(philo);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philo_list *philo)
{
	printf_wrapper(2, philo->mutex_write, philo->id, philo->time_init);
	ft_usleep(philo->time_sleep * 1000);
}

void	philo_think(t_philo_list *philo)
{
	printf_wrapper(3, philo->mutex_write, philo->id, philo->time_init);
	ft_usleep(1000 * philo->time_think);
}

void	philo_eat(t_philo_list *philo)
{
	char	could_get_right;
	char	could_get_left;

	could_get_right = 0;
	could_get_left = 0;
	while (1)
	{
		if (end_value(philo) || check_philo_dead(philo))
			break ;
		could_get_right = try_to_set_one(philo->fork_right, philo->mutex_right);
		if (could_get_right)
		{
			could_get_left = try_to_set_one(philo->fork_left, philo->mutex_left);
			if (could_get_left)
			{
				gettimeofday(philo->time_last_ate, NULL);
				printf_wrapper(0, philo->mutex_write, philo->id, philo->time_init);
				printf_wrapper(0, philo->mutex_write, philo->id, philo->time_init);
				printf_wrapper(1, philo->mutex_write, philo->id, philo->time_init);
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
