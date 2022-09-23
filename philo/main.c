/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:35:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/23 02:28:08 by mde-arpe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*malloc(size_t n)
// {
// 	static int cnt = 0;

// 	if (cnt == MALLOC_FAIL)
// 		return (NULL);
// 	cnt++;
// 	return (calloc(n, 1));
// }

// void	leaks(void)
// {
// 	system("leaks philosophers");
// }

//status 0 if fail
//-1 in last parameter means no limit of iteractions
static int	*parse(int argc, char **argv)
{
	int	*ret;
	int	status_atoi;
	int	counter;

	if (argc < 5 || argc > 6)
		return (write(2, "Number of args must be 4 or 5\n", 30), NULL);
	ret = malloc(6 * 4);
	if (!ret)
		return (write(2, "Malloc fail\n", 12), NULL);
	counter = 1;
	while (argv[counter])
	{
		ret[counter - 1] = ft_atoi(argv[counter], &status_atoi);
		if (!status_atoi || ret[counter - 1] <= 0)
		{
			free(ret);
			return (write(2, "Couldnt parse args, "
					"check that they are positive integers\n", 58), NULL);
		}
		counter++;
	}
	if (counter == 5)
		ret[4] = -1;
	ret[5] = 0;
	return (ret);
}

int	garbaje_coll(int *args, pthread_mutex_t *mutex1,
						pthread_mutex_t *mutex2, const char *msg)
{
	if (args)
		free(args);
	if (mutex1)
		pthread_mutex_destroy(mutex1);
	if (mutex2)
		pthread_mutex_destroy(mutex2);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (1);
}

int	main(int argc, char **argv)
{
	int				*args;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	mutex_end;
	t_philo_list	*philo_l;
	t_thread_list	*thread_l;

	args = parse(argc, argv);
	if (!args)
		return (1);
	if (pthread_mutex_init(&mutex_write, NULL))
		return (garbaje_coll(args, NULL, NULL, "Mutex init fail\n"));
	if (pthread_mutex_init(&mutex_end, NULL))
		return (garbaje_coll(args, &mutex_write, NULL, "Mutex init fail\n"));
	philo_l = philo_create(args, &mutex_write, &mutex_end);
	if (!philo_l)
		return (garbaje_coll(args, &mutex_write, &mutex_end,
				"Philo list init fail\n"));
	thread_l = thread_create(args, philo_l);
	if (!thread_l)
		return (free_philo_list(philo_l), garbaje_coll(args, &mutex_write,
				&mutex_end, "Philo thread init fail\n"));
	thread_wait(thread_l);
	free_thread_list(thread_l);
	free_philo_list(philo_l);
	garbaje_coll(args, &mutex_write, &mutex_end, NULL);
}
