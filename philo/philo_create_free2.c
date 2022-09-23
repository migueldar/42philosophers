/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_free2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 01:43:06 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/23 01:46:14 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_left_forks(t_philo_list *list)
{
	pthread_mutex_t	*aux;
	int				*aux_int;

	aux = list->mutex_right;
	aux_int = list->fork_right;
	list = list->next;
	while (list->id != 1)
	{
		list->mutex_left = aux;
		list->fork_left = aux_int;
		aux = list->mutex_right;
		aux_int = list->fork_right;
		list = list->next;
	}
	list->mutex_left = aux;
	list->fork_left = aux_int;
}

void	free_philo_list(t_philo_list *list)
{
	t_philo_list	*aux;
	t_philo_list	*head;

	head = list;
	while (list && 42)
	{
		pthread_mutex_destroy(list->mutex_right);
		free(list->mutex_right);
		free(list->fork_right);
		free(list->time_init);
		free(list->time_last_ate);
		aux = list->next;
		free(list);
		if (aux == head)
			break ;
		list = aux;
	}
}
