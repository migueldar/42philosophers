/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-arpe <mde-arpe@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 22:35:55 by mde-arpe          #+#    #+#             */
/*   Updated: 2022/09/25 23:27:20 by mde-arpe         ###   ########.fr       */
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

void	leaks(void)
{
	system("leaks philosophers");
}

//status 0 if fail
//-1 in last parameter means no limit of iteractions
static int	*parse(int argc, char **argv)
{
	int	*ret;
	int	status_atoi;
	int	counter;

	if (argc < 5 || argc > 6)
		return (write(2, "Number of args must be 4 or 5\n", 30), NULL);
	ret = malloc(5 * 4);
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
		ret[4] = -2;
	return (ret);
}

int	garbaje_coll(int *args, t_philo *philo, const char *msg)
{
	if (args)
		free(args);
	if (philo)
	{
		close_semaphores(philo);
		unlink_semaphores();
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (1);
}

//TODO
//data races
int	main(int argc, char **argv)
{
	int			*args;
	int			status;
	t_philo		philo;
	t_pid_list	*pid_list;

	unlink_semaphores();
	args = parse(argc, argv);
	if (!args)
		return (1);
	philo = create_philo(args);
	status = create_semaphores(args[0], &philo);
	if (!status)
		return (garbaje_coll(args, &philo, "Semaphores creation fail\n"), 1);
	pid_list = create_processes(args[0], &philo);
	if (!pid_list)
		return (garbaje_coll(args, &philo, "Fork fail\n"), 1);
	processes_kill(pid_list);
	free_pid_list(pid_list);
	garbaje_coll(args, &philo, NULL);
}
