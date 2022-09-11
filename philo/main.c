/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:35:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/11 04:50:33 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leaks()
{
	system("leaks philosophers");
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
	pthread_mutex_t mutex_end;
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
	*end = 0;
	pthread_mutex_init(&(mutex_write), NULL);
	pthread_mutex_init(&(mutex_end), NULL);
	philo_l = NULL;
	while (++counter <= args[0])
	{
		aux = new_philo(args, counter, &mutex_write, &mutex_end, end);
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