/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 01:58:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 22:26:43 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	create_philo(int *args)
{
	t_philo	new;

	new.number_philos = args[0];
	new.time_die = args[1];
	new.time_eat = args[2];
	new.time_sleep = args[3];
	new.time_think = new.time_eat - new.time_sleep + 2;
	if (new.time_think < 0)
		new.time_think = 0;
	new.number_eat = args[4] + 1;
	gettimeofday(&(new.time_init), NULL);
	new.time_last_ate = new.time_init;
	return (new);
}
