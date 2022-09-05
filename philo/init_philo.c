/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:43:36 by hrings            #+#    #+#             */
/*   Updated: 2022/05/20 11:47:44 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_first(t_philo *philo, t_philosopher *philosophers);
static void	init_rest(t_philo *philo, t_philosopher *philosophers);

void	init_philo(t_philo *philo, t_philosopher *philosophers)
{
	init_first(philo, philosophers);
	init_rest(philo, philosophers);
}

static void	init_first(t_philo *philo, t_philosopher *philosophers)
{
	philosophers[0].num = 0;
	philosophers[0].meal_check = (pthread_mutex_t *) \
								malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(philosophers[0].meal_check, NULL))
		error_handler(philo, MUTEXERROR);
	philosophers[0].meals_needed = philo->num_must_eat;
	philosophers[0].last_meal = timestamp();
	philosophers[0].left_fork = &philo->forks[1];
	philosophers[0].right_fork = &philo->forks[0];
	philosophers[0].info = philo;
}

static void	init_rest(t_philo *philo, t_philosopher *philosophers)
{
	int	index;

	index = 1;
	while (index < philo->num_philo)
	{
		philosophers[index].num = index;
		philosophers[index].meal_check = (pthread_mutex_t *) \
									malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philosophers[index].meal_check, NULL))
			error_handler(philo, MUTEXERROR);
		philosophers[index].meals_needed = philo->num_must_eat;
		philosophers[index].last_meal = timestamp();
		philosophers[index].left_fork = &philo->forks[index];
		philosophers[index].right_fork = \
		&philo->forks[(index + 1) % philo->num_philo];
		philosophers[index].info = philo;
		index++;
	}
}
