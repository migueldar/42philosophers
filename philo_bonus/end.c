/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 08:39:50 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 09:17:53 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_to_one(t_philo *philo)
{
	sem_wait(philo->mutex_end);
	philo->end = 1;
	sem_post(philo->mutex_end);
}

int	end_value(t_philo *philo)
{
	int	ret;

	sem_wait(philo->mutex_end);
	ret = philo->end;
	sem_post(philo->mutex_end);
	return (ret);
}
