/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 01:58:26 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/16 21:30:20 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//malloc fail
//mutex fail
//remove intermediate step where mutex_right is set as aux
t_philo_list	*new_philo(int *args, int counter, pthread_mutex_t *mutex_write, pthread_mutex_t *mutex_end)
{
	t_philo_list	*new;

	new = malloc(sizeof(t_philo_list));
	if (!new)
		return (NULL);
	new->mutex_right = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->mutex_right, NULL);
	new->fork_right = malloc(4);
	*(new->fork_right) = 0;
	new->mutex_write = mutex_write;
	new->mutex_end = mutex_end;
	new->id = counter;
	new->time_die = args[1];
	new->time_eat = args[2];
	new->time_sleep = args[3];
	new->number_eat = args[4];
	new->end = &args[5];
	new->time_init = malloc(sizeof(struct timeval));
	new->time_last_ate = malloc(sizeof(struct timeval));
	gettimeofday(new->time_init, NULL);
	*(new->time_last_ate) = *(new->time_init);
	return (new);
}

void	add_philo(t_philo_list **philo_list, t_philo_list *new)
{
	t_philo_list	*aux;

	if (!*philo_list)
	{
		new->next = new;
		*philo_list = new;
		return ;	
	}
	aux = (*philo_list)->next;
	(*philo_list)->next = new;
	new->next = aux;
}

void	add_left_forks(t_philo_list *list)
{
	pthread_mutex_t *aux;
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

//consider 1 philo
void	free_philo_list(t_philo_list *list)
{
	t_philo_list	*aux;
	t_philo_list	*head;

	head = list;
	while (42)
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
