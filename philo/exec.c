/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 02:51:56 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/10 05:17:32 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_exec(void *philo_void)
{
	t_philo_list *philo;
	
	philo = (t_philo_list *) philo_void;

	pthread_mutex_lock(philo->mutex_write);
	printf("%d started\n", philo->id);
	pthread_mutex_unlock(philo->mutex_write);
	usleep(1000);
	printf_wrapper(2, philo->mutex_write, philo->id);
	return NULL;
}