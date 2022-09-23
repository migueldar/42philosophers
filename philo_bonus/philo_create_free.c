/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 01:58:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/23 02:15:56 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(int *args)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->time_init = malloc(sizeof(struct timeval));
	if (!(new->time_init))
		return (free(new), NULL);
	new->time_last_ate = malloc(sizeof(struct timeval));
	if (!(new->time_last_ate))
		return (free(new->time_init), free(new->time_last_ate), NULL);
	new->time_die = args[1];
	new->time_eat = args[2];
	new->time_sleep = args[3];
	new->time_think = new->time_eat - new->time_sleep + 2;
	if (new->time_think < 0)
		new->time_think = 0;
	new->number_eat = args[4];
	gettimeofday(new->time_init, NULL);
	*(new->time_last_ate) = *(new->time_init);
	new->end = 0;
	return (new);
}

void	free_philo(t_philo *philo)
{
	free(philo->time_init);
	free(philo->time_last_ate);
	free(philo);
}
