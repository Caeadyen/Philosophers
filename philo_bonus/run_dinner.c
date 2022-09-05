/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:27:41 by hrings            #+#    #+#             */
/*   Updated: 2022/09/05 10:42:23 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	run_one_phil(t_philo *philo);
static void	init_sema(t_philo *philo);
static void	init_philo(t_philo *philo);
static void	launch_fork(t_philo *philo);

void	run_dinner(t_philo *philo)
{
	if (philo->num_philo == 1)
		run_one_phil(philo);
	else
	{
		init_sema(philo);
		init_philo(philo);
		philo->start_time = timestamp();
		launch_fork(philo);
	}
}

static void	run_one_phil(t_philo *philo)
{
	philo->start_time = timestamp();
	printf("%li %i %s\n", timestamp() - philo->start_time, 0, FORKTAKEN);
	ft_usleep(philo->time_to_die);
	printf("%li %i %s\n", timestamp() - philo->start_time, 0, "died");
}

static void	init_sema(t_philo *philo)
{
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->num_philo);
	if (philo->forks == NULL)
		error_handler(philo, SEMAERROR);
	sem_unlink("forks");
	philo->writing = sem_open("writing", O_CREAT, 0644, 1);
	if (philo->writing == NULL)
		error_handler(philo, SEMAERROR);
	sem_unlink("writing");
	philo->death_check = sem_open("death_check", O_CREAT, 0644, 1);
	if (philo->death_check == NULL)
		error_handler(philo, SEMAERROR);
	sem_unlink("death_check");
	philo->finished = sem_open("finished", O_CREAT, 0644, 0);
	if (philo->finished == NULL)
		error_handler(philo, SEMAERROR);
	sem_unlink("finished");
	philo->num_meal_check = sem_open("num_meal_check", O_CREAT, 0644, 0);
	if (philo->num_meal_check == NULL)
		error_handler(philo, SEMAERROR);
	sem_unlink("num_meal_check");
}

static void	init_philo(t_philo *philo)
{
	int	index;

	philo->philosophers = (t_philosopher *)malloc(philo->num_philo \
											* sizeof(t_philosopher));
	if (philo->philosophers == NULL)
		exit(1);
	index = 0;
	while (index < philo->num_philo)
	{
		philo->philosophers[index].meal_check = sem_open("meal_check", \
													O_CREAT, 0644, 1);
		if (philo->philosophers[index].meal_check == NULL)
			error_handler(philo, SEMAERROR);
		sem_unlink("meal_check");
		philo->philosophers[index].meals_needed = philo->num_must_eat;
		philo->philosophers[index].last_meal = timestamp();
		philo->philosophers[index].info = philo;
		philo->philosophers[index].num = index;
		index++;
	}
}

static void	launch_fork(t_philo *philo)
{
	int			index;

	index = 0;
	while (index < philo->num_philo)
	{
		philo->philosophers[index].id = fork();
		if (philo->philosophers[index].id == 0)
		{
			active_phil(&(philo->philosophers[index]));
			exit(0);
		}
		else if (philo->philosophers[index].id < 0)
			error_handler(philo, FORKERROR);
		index++;
	}
	start_threads(philo);
}
