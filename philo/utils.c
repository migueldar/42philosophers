/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:31:10 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/22 05:54:03 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//counter acts as strlen
//status 0 if fail
int	ft_atoi(const char *str, int *status)
{
	int				minus;
	long int		ret;
	int				counter;

	ret = 0;
	minus = 0;
	counter = 0;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			minus++;
	while (*str)
	{
		if (!(*str <= '9' && *str >= '0'))
			return (*status = 0, 0);
		ret = ret * 10 + (*str++ - '0');
		counter++;
	}
	if (counter > 10 || (ret > 0x7fffffff && !minus)
		|| (ret > 0x80000000 && minus))
		return (*status = 0, 0);
	if (minus)
		ret *= -1;
	return (*status = 42, ret);
}

//type 0 fork, 1 eat, 2 sleep, 3 think, 4 die
void	printf_wrapper(int type, pthread_mutex_t *write_mutex,
	int philo_id, struct timeval *time_init)
{
	struct timeval	time_curr;
	long long		time_since_beg;

	gettimeofday(&time_curr, NULL);
	time_since_beg = (time_curr.tv_sec - time_init->tv_sec) * 1000;
	time_since_beg += (time_curr.tv_usec - time_init->tv_usec) / 1000;
	pthread_mutex_lock(write_mutex);
	if (type == 0)
		printf("%s[%lldms] %d has taken a fork%s\n",
			CYAN, time_since_beg, philo_id, FN);
	else if (type == 1)
		printf("%s[%lldms] %d is eating%s\n",
			BLUE, time_since_beg, philo_id, FN);
	else if (type == 2)
		printf("%s[%lldms] %d is sleeping%s\n",
			GREEN, time_since_beg, philo_id, FN);
	else if (type == 3)
		printf("%s[%lldms] %d is thinking%s\n",
			PINK, time_since_beg, philo_id, FN);
	else if (type == 4)
		printf("%s[%lldms] %d died%s\n", RED, time_since_beg, philo_id, FN);
	pthread_mutex_unlock(write_mutex);
}

int	end_value(t_philo_list *philo)
{
	int	ret;

	pthread_mutex_lock(philo->mutex_end);
	ret = *(philo->end);
	pthread_mutex_unlock(philo->mutex_end);
	return (ret);
}

void	end_to_true(t_philo_list *philo)
{
	pthread_mutex_lock(philo->mutex_end);
	*(philo->end) = 1;
	pthread_mutex_unlock(philo->mutex_end);
}

int	ft_strlen(const char *str)
{
	int	ret;

	ret = 0;
	while (str && *(str++))
		ret++;
	return (ret);
}
