/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 09:08:02 by hrings            #+#    #+#             */
/*   Updated: 2022/08/01 07:58:38 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	check_input(t_philo *philo, int argc, char **argv);
static void	init_philo(t_philo *philo);

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
		init_philo(philo);
		if (philo->num_must_eat != 0)
		{
			run_dinner(philo);
			clean_up(philo);
		}
		else
			free(philo);
	}
	return (0);
}

static void	check_input(t_philo *philo, int argc, char **argv)
{
	philo->error = 0;
	philo->num_philo = ft_atoi_phil(argv[1], philo);
	if (philo->num_philo == 0)
		philo->error = 1;
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

static void	init_philo(t_philo *philo)
{
	philo->death_check = NULL;
	philo->forks = NULL;
	philo->writing = NULL;
	philo->finished = NULL;
	philo->num_meal_check = NULL;
	philo->philosophers = NULL;
}
