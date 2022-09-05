/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_dinner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 11:27:41 by hrings            #+#    #+#             */
/*   Updated: 2022/07/28 09:00:11 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	run_one_phil(t_philo *philo);
static void	init_mutex(t_philo *philo);
static void	launch_thread(t_philo *philo);

void	run_dinner(t_philo *philo)
{
	if (philo->num_philo == 1)
		run_one_phil(philo);
	else
	{
		philo->start_time = timestamp();
		init_mutex(philo);
		launch_thread(philo);
	}
}

static void	run_one_phil(t_philo *philo)
{
	philo->start_time = timestamp();
	printf("%li %i %s\n", timestamp() - philo->start_time, 0, FORKTAKEN);
	ft_usleep(philo->time_to_sleep);
	printf("%li %i %s\n", timestamp() - philo->start_time, 0, "died");
	clean_up_one(philo);
}

static void	init_mutex(t_philo *philo)
{
	int	index;

	philo->forks = (pthread_mutex_t *)malloc(philo->num_philo * \
											sizeof(pthread_mutex_t));
	philo->writing = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->meal_check = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->death_check = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	index = 0;
	while (index < philo->num_philo)
	{
		if (pthread_mutex_init(&(philo->forks[index++]), NULL))
			error_handler(philo, MUTEXERROR);
	}
	if (pthread_mutex_init(philo->writing, NULL))
		error_handler(philo, MUTEXERROR);
	if (pthread_mutex_init(philo->death_check, NULL))
		error_handler(philo, MUTEXERROR);
	if (pthread_mutex_init(philo->meal_check, NULL))
		error_handler(philo, MUTEXERROR);
}

static void	launch_thread(t_philo *philo)
{
	int				index;
	t_philosopher	*philosophers;

	index = 0;
	philosophers = (t_philosopher *)malloc(philo->num_philo * \
										sizeof(t_philosopher));
	init_philo(philo, philosophers);
	philo->philosophers = philosophers;
	while (index < philo->num_philo)
	{
		if (pthread_create(&philosophers[index].id, NULL, \
					active_phil, &philosophers[index]))
			error_handler(philo, THREADERROR);
		index++;
	}
	if (philo->num_must_eat > 0)
		run_eat_checker(philo);
	index = 0;
	while (index < philo->num_philo)
	{
		pthread_join(philosophers[index].id, NULL);
		index++;
	}
	clean_up_phil(philosophers);
}
