/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrings <hrings@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:09:11 by hrings            #+#    #+#             */
/*   Updated: 2022/07/28 09:18:07 by hrings           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	clean_up_phil(t_philosopher *philosophers)
{
	int	index;

	index = 0;
	while (index < philosophers->info->num_philo)
	{
		pthread_mutex_destroy(philosophers[index].meal_check);
		free(philosophers[index].meal_check);
		index++;
	}
	free(philosophers);
}

void	clean_up(t_philo *philo)
{
	int	index;

	pthread_mutex_destroy(philo->writing);
	pthread_mutex_destroy(philo->death_check);
	pthread_mutex_destroy(philo->meal_check);
	index = 0;
	while (index < philo->num_philo)
		pthread_mutex_destroy(&(philo->forks[index++]));
	free(philo->forks);
	free(philo->writing);
	free(philo->meal_check);
	free(philo->death_check);
	free(philo);
}

void	clean_up_one(t_philo *philo)
{
	free(philo);
	exit(0);
}
