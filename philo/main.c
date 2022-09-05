/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:08:02 by hrings            #+#    #+#             */
/*   Updated: 2022/08/01 07:57:10 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	check_input(t_philo *philo, int argc, char **argv);

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc > 6 || argc < 5)
	{
		printf("Missing Argument: needed Arguments are: ");
		printf("number_of_philosophers time_to_die time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}
	else
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			exit(1);
		check_input(philo, argc, argv);
		philo->all_done = 1;
		philo->philo_eaten = 0;
		if (philo->num_must_eat != 0)
		{
			run_dinner(philo);
			clean_up(philo);
		}
	}
	return (0);
}

static void	check_input(t_philo *philo, int argc, char **argv)
{
	philo->error = 0;
	philo->num_philo = ft_atoi_phil(argv[1], philo);
	philo->time_to_die = ft_atoi_phil(argv[2], philo);
	philo->time_to_eat = ft_atoi_phil(argv[3], philo);
	philo->time_to_sleep = ft_atoi_phil(argv[4], philo);
	if (argc == 6)
		philo->num_must_eat = ft_atoi_phil(argv[5], philo);
	else
		philo->num_must_eat = -1;
	if (philo->error)
		error_handler(philo, INPUTERROR);
}
