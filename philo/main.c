/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:35:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/10 05:37:25 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//type 0 fork, 1 eat, 2 sleep, 3 think, 4 die
void	printf_wrapper(int type, pthread_mutex_t *write_mutex, int philo_id)
{
	pthread_mutex_lock(write_mutex);
	if (type == 0)
		printf("%s[time_in_ms] %d has taken a fork %s\n", cyan, philo_id, fn);
	else if (type == 1)
		printf("%s[time_in_ms] %d is eating %s\n", blue, philo_id, fn);
	else if (type == 2)
		printf("%s[time_in_ms] %d is sleeping %s\n", green, philo_id, fn);
	else if (type == 3)
		printf("%s[time_in_ms] %d is thinking %s\n", magenta, philo_id, fn);
	else if (type == 4)
		printf("%s[time_in_ms] %d died %s\n", red, philo_id, fn);
	pthread_mutex_unlock(write_mutex);
}

void	leaks()
{
	system("leaks philosophers");
}

void	add_left_forks(t_philo_list *list)
{
	pthread_mutex_t *aux;

	aux = list->mutex_right;
	list = list->next;
	while (list->id != 1)
	{
		list->mutex_left = aux;
		aux = list->mutex_right;
		list = list->next;
	}
	list->mutex_left = aux;
}

//status 0 if fail
//-1 in last parameter means no limit of iteractions
int	*parse(char **argv, int *status)
{
	int	*ret;
	int status_atoi;
	int	counter;

	ret = malloc(5 * 4);
	counter = 1;
	while (argv[counter])
	{
		ret[counter - 1] = ft_atoi(argv[counter], &status_atoi);
		if (!status_atoi || ret[counter - 1] < 0)
		{
			free(ret);
			return (*status = 0, NULL);
		}
		counter++;
	}
	if (counter == 5)
		ret[4] = -1;
	return (*status = 42, ret);
}

void	add_thread(t_thread_list **thread_list, t_thread_list *new)
{
	if (!*thread_list)
	{
		*thread_list = new;
		return ;	
	}
	new->next = *thread_list;
	*thread_list = new;
}

//create fail manage
t_thread_list	*new_thread(t_philo_list *philo)
{
	t_thread_list	*ret;

	ret = malloc(sizeof(t_thread_list));
	ret->thread = malloc(sizeof(pthread_t));
	pthread_create(ret->thread, NULL, philo_exec, philo);
	ret->next = NULL;
	return (ret);
}

//malloc fail
//mutex fail
//remove intermediate step where mutex_right is set as aux
t_philo_list	*new_philo(int *args, int counter, pthread_mutex_t *mutex_write, int *end)
{
	t_philo_list	*new;

	new = malloc(sizeof(t_philo_list));
	if (!new)
		return NULL;
	new->mutex_right = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(new->mutex_right, NULL);
	new->fork_l = 0;
	new->fork_r = 0;
	new->mutex_write = mutex_write;
	new->end = end;
	new->id = counter;
	new->time_die = args[1];
	new->time_eat = args[2];
	new->time_sleep = args[3];
	new->number_eat = args[4];
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

//TODO
//manage case where philo || seconds is 0
//manage mutex init all
//think about 1 philo
//free everything
int	main(int argc, char **argv)
{
	atexit(leaks);
	int			*args;
	int			status;
	int			counter;
	pthread_mutex_t mutex_write;
	t_philo_list *philo_l;
	t_philo_list *aux;
	t_thread_list *thread_l;
	t_thread_list *thread_aux;
	int			*end;

	if (argc < 5 || argc > 6)
		return (write(2, "Number of args must be 4 or 5\n", 31), 1);
	args = parse(argv, &status);
	if (!status)
		return (write(2, "Couldnt parse args, check that they are positive integers\n", 59), 1);
	counter = 0;
	end = malloc(4);
	end[0] = 0;
	pthread_mutex_init(&(mutex_write), NULL);
	philo_l = NULL;
	while (++counter <= args[0])
	{
		aux = new_philo(args, counter, &mutex_write, end);
		add_philo(&philo_l, aux);
	}
	add_left_forks(philo_l);
	counter = 0;
	thread_l = NULL;
	while (++counter <= args[0])
	{
		thread_aux = new_thread(philo_l);
		add_thread(&thread_l, thread_aux);
		philo_l = philo_l->next;
	}
	counter = 0;
	while (++counter <= args[0])
	{
		pthread_join(*(thread_l->thread), NULL);
		thread_l = thread_l->next;
	}
	free(args);
	return (0);
}